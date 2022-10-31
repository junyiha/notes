## 外网通过ngrok连接公司内网

+ `ngrok config add-authtoken 2Fyd9ZRXPYDbBNIZQRXAPd036Un_cCTH2CsrmttkSzKE1ind`

+ `ngrok tcp 22 `

+ `ssh user@0.tcp.jp.ngrok.io -p 11111`