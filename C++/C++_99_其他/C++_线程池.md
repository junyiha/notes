## 简介

+ C++ 线程池的应用

## boost.asio

+ boost::asio::thread_pool类
+ 结合mongoose，搭建异步http服务器，示例代码如下:
```cpp
int http_server_with_mongoose()
{
    struct HttpMessage
    {
        std::string path;
        std::string method;
        std::string body;

        std::string response_type;
        std::string response_body;
    };

    class HttpWithMongoose
    {
    private:
        struct mg_mgr mgr;
        struct mg_connection *connect;
        boost::asio::thread_pool tp;

    public:
        HttpWithMongoose() : tp(8)
        {
            mg_mgr_init(&mgr);
        }
        virtual ~HttpWithMongoose()
        {
            mg_mgr_free(&mgr);
        }

    public:
        void Start()
        {
            connect = mg_http_listen(&mgr, "0.0.0.0:9999", handle_event, this);

            while (true)
            {
                mg_mgr_poll(&mgr, 50);
            }
        }

    private:
        void Dispath(HttpMessage& http_message)
        {
            LOG(INFO) << "path: " << http_message.path << "\n"
                      << "method: " << http_message.method << "\n"
                      << "body: " << http_message.body << "\n";
            
            http_message.response_type = "Content-type: application/json";

            nlohmann::json reply_data;
            reply_data["hello"] = "http with mongoose!";
            http_message.response_body = reply_data.dump();
        }

    private:
        static void handle_event(mg_connection *connect, int ev, void *ev_data, void *fn_data)
        {
            HttpWithMongoose* this_ptr = static_cast<HttpWithMongoose *>(fn_data);
            struct mg_http_message* hm = static_cast<struct mg_http_message*>(ev_data);

            switch (ev)
            {
                case MG_EV_HTTP_MSG:
                {
                    HttpMessage http_message;

                    http_message.path = std::string(hm->uri.ptr, hm->uri.len);
                    http_message.method = std::string(hm->method.ptr, hm->method.len);
                    http_message.body = std::string(hm->body.ptr, hm->body.len);

                    // std::thread tmp_thread = std::thread([](HttpMessage http_message, HttpWithMongoose* this_ptr, struct mg_connection* connect)
                    // {
                    //     this_ptr->Dispath(http_message);

                    //     mg_http_reply(connect, 200, http_message.response_type.c_str(), http_message.response_body.c_str());
                    //     connect->is_draining = 1;
                    // }, http_message, this_ptr, connect);
                    // tmp_thread.detach();

                    auto dpcp = [](HttpMessage http_message, HttpWithMongoose* this_ptr, struct mg_connection* connect)
                    {
                        this_ptr->Dispath(http_message);

                        mg_http_reply(connect, 200, http_message.response_type.c_str(), http_message.response_body.c_str());
                        connect->is_draining = 1;
                    };
                    boost::asio::post(this_ptr->tp, std::bind(dpcp, http_message, this_ptr, connect));

                    break;
                }
            }
        }
    };

    HttpWithMongoose http_server;

    http_server.Start();

    return 0;
}
```