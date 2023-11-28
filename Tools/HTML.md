## 简介

+ HTML相关的笔记

## HTML 简介

+ 什么是HTML?
  + HTML 是用来描述网页的一种语言。
  + HTML 指的是超文本标记语言: HyperText Markup Language
  + HTML 不是一种编程语言，而是一种标记语言
  + 标记语言是一套标记标签 (markup tag)
  + HTML 使用标记标签来描述网页
  + HTML 文档包含了HTML 标签及文本内容
  + HTML文档也叫做 web 页面

+ HTML 标签
  + HTML 标记标签通常被称为 HTML 标签 (HTML tag)。
  + HTML 标签是由尖括号包围的关键词，比如 <html>
  + HTML 标签通常是成对出现的，比如 <b> 和 </b>
  + 标签对中的第一个标签是开始标签，第二个标签是结束标签
  + 开始和结束标签也被称为开放标签和闭合标签

+ HTML 元素
  + "HTML 标签" 和 "HTML 元素" 通常都是描述同样的意思.
  + 但是严格来讲, 一个 HTML 元素包含了开始标签与结束标签，如下实例:
  + HTML 元素:
```html
<p>这是一个段落。</p>
```

+ Web 浏览器
  + Web浏览器（如谷歌浏览器，Internet Explorer，Firefox，Safari）是用于读取HTML文件，并将其作为网页显示。
  + 浏览器并不是直接显示的HTML标签，但可以使用标签来决定如何展现HTML页面的内容给用户：

+ HTML版本
  + HTML	    1991
  + HTML+	    1993
  + HTML 2.0	1995
  + HTML 3.2	1997
  + HTML 4.01	1999
  + XHTML 1.0	2000
  + HTML5	    2012
  + XHTML5	    2013

+ <!DOCTYPE> 声明
  + <!DOCTYPE>声明有助于浏览器中正确显示网页。
  + 网络上有很多不同的文件，如果能够正确声明HTML的版本，浏览器就能正确显示网页内容。
  + doctype 声明是不区分大小写的，以下方式均可：
```html
<!DOCTYPE html>

<!DOCTYPE HTML>

<!doctype html>

<!Doctype Html>
```

+ 通用声明
  + HTML5
```html
<!DOCTYPE html>
```
  + HTML 4.01
```html
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
```
  + XHTML 1.0
```html
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
```

+ 中文编码
  + 目前在大部分浏览器中，直接输出中文会出现中文乱码的情况，这时候我们就需要在头部将字符声明为 UTF-8 或 GBK。
```html
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>
页面标题</title>
</head>
<body>
 
<h1>我的第一个标题</h1>
 
<p>我的第一个段落。</p>
 
</body>
</html>
```

## HTML基础

+ HTML 标题
  + HTML 标题（Heading）是通过<h1> - <h6> 标签来定义的。
```html
<h1>这是一个标题</h1>
<h2>这是一个标题</h2>
<h3>这是一个标题</h3>
```

+ HTML 段落
  + HTML 段落是通过标签 <p> 来定义的。
```html
<p>这是一个段落。</p>
<p>这是另外一个段落。</p>
```

+ HTML 链接
  + HTML 链接是通过标签 <a> 来定义的。
```html
<a href="https://www.runoob.com">这是一个链接</a>
```
  + 提示:在 href 属性中指定链接的地址。

+ HTML 图像
  + HTML 图像是通过标签 <img> 来定义的.
```html
<img src="/images/logo.png" width="258" height="39" />
```

## HTML 元素

+ HTML 文档由 HTML 元素定义。
  + <p>	这是一个段落	</p>
  + <a href="default.htm">	这是一个链接	</a>
  + <br>	换行
  + *开始标签常被称为起始标签（opening tag），结束标签常称为闭合标签（closing tag）

+ HTML 元素语法
  + HTML 元素以开始标签起始
  + HTML 元素以结束标签终止
  + 元素的内容是开始标签与结束标签之间的内容
  + 某些 HTML 元素具有空内容（empty content）
  + 空元素在开始标签中进行关闭（以开始标签的结束而结束）
  + 大多数 HTML 元素可拥有属性

+ 嵌套的 HTML 元素
  + 大多数 HTML 元素可以嵌套（HTML 元素可以包含其他 HTML 元素）。
  + HTML 文档由相互嵌套的 HTML 元素构成。

+ HTML 空元素
  + 没有内容的 HTML 元素被称为空元素。空元素是在开始标签中关闭的。
  + <br> 就是没有关闭标签的空元素（<br> 标签定义换行）。
  + 在 XHTML、XML 以及未来版本的 HTML 中，所有元素都必须被关闭。
  + 在开始标签中添加斜杠，比如 <br />，是关闭空元素的正确方法，HTML、XHTML 和 XML 都接受这种方式。
  + 即使 <br> 在所有浏览器中都是有效的，但使用 <br /> 其实是更长远的保障。

+ HTML 提示：使用小写标签
  + HTML 标签对大小写不敏感：<P> 等同于 <p>。许多网站都使用大写的 HTML 标签。
  + 菜鸟教程使用的是小写标签，因为万维网联盟（W3C）在 HTML 4 中推荐使用小写，而在未来 (X)HTML 版本中强制使用小写。

## HTML 属性

+ 属性是 HTML 元素提供的附加信息。

+ HTML 属性
  + HTML 元素可以设置属性
  + 属性可以在元素中添加附加信息
  + 属性一般描述于开始标签
  + 属性总是以名称/值对的形式出现，比如：name="value"。

+ 属性实例
  + HTML 链接由 <a> 标签定义。链接的地址在 href 属性中指定：
```html
<a href="http://www.runoob.com">这是一个链接</a>
```

+ HTML 属性常用引用属性值
  + 属性值应该始终被包括在引号内。
  + 双引号是最常用的，不过使用单引号也没有问题。
  + 提示: 在某些个别的情况下，比如属性值本身就含有双引号，那么您必须使用单引号，例如：
```html
name='John "ShotGun" Nelson'
```

+ HTML 提示：使用小写属性
  + 属性和属性值对大小写不敏感。
  + 不过，万维网联盟在其 HTML 4 推荐标准中推荐小写的属性/属性值。
  + 而新版本的 (X)HTML 要求使用小写属性。

+ HTML 属性参考手册
  + 下面列出了适用于大多数 HTML 元素的属性：
  + class	为html元素定义一个或多个类名（classname）(类名从样式文件引入)
  + id	    定义元素的唯一id
  + style	规定元素的行内样式（inline style）
  + title	描述了元素的额外信息 (作为工具条使用)

## HTML 标题

+ HTML 标题
  + 标题（Heading）是通过 <h1> - <h6> 标签进行定义的。
  + <h1> 定义最大的标题。 <h6> 定义最小的标题。
```html
<h1>这是一个标题。</h1>
<h2>这是一个标题。</h2>
<h3>这是一个标题。</h3>
```
  + 注释: 浏览器会自动地在标题的前后添加空行。

+ 标题很重要
  + 请确保将 HTML 标题 标签只用于标题。不要仅仅是为了生成粗体或大号的文本而使用标题。
  + 搜索引擎使用标题为您的网页的结构和内容编制索引。
  + 因为用户可以通过标题来快速浏览您的网页，所以用标题来呈现文档结构是很重要的。
  + 应该将 h1 用作主标题（最重要的），其后是 h2（次重要的），再其次是 h3，以此类推。

+ HTML 水平线
  + <hr> 标签在 HTML 页面中创建水平线。
  + hr 元素可用于分隔内容。
```html
<p>这是一个段落。</p>
<hr>
<p>这是一个段落。</p>
<hr>
<p>这是一个段落。</p>
```

+ HTML 注释
  + 可以将注释插入 HTML 代码中，这样可以提高其可读性，使代码更易被人理解。浏览器会忽略注释，也不会显示它们
  + 注释写法如下:
```html
<!-- 这是一个注释 -->
```
  + 注释: 开始括号之后（左边的括号）需要紧跟一个叹号 ! (英文标点符号)，结束括号之前（右边的括号）不需要，合理地使用注释可以对未来的代码编辑工作产生帮助。

+ HTML 提示 - 如何查看源代码
  + 你是否看过一些网页然后惊叹它是如何实现的。
  + 如果您想找到其中的奥秘，只需要单击右键，然后选择"查看源文件"（IE）或"查看页面源代码"（Firefox），其他浏览器的做法也是类似的。这么做会打开一个包含页面 HTML 代码的窗口。

## HTML 段落

+ HTML 段落
  + 段落是通过 <p> 标签定义的。
```html
<p>这是一个段落 </p>
<p>这是另一个段落</p>
```
  + 注意：浏览器会自动地在段落的前后添加空行。（</p> 是块级元素）

+ HTML 折行
  + 如果您希望在不产生一个新段落的情况下进行换行（新行），请使用 <br> 标签：
```html
<p>这个<br>段落<br>演示了分行的效果</p>
```
  + <br /> 元素是一个空的 HTML 元素。由于关闭标签没有任何意义，因此它没有结束标签。

+ HTML 输出- 使用提醒
  + 我们无法确定 HTML 被显示的确切效果。屏幕的大小，以及对窗口的调整都可能导致不同的结果。
  + 对于 HTML，您无法通过在 HTML 代码中添加额外的空格或换行来改变输出的效果。
  + 当显示页面时，浏览器会移除源代码中多余的空格和空行。所有连续的空格或空行都会被算作一个空格。需要注意的是，HTML 代码中的所有连续的空行（换行）也被显示为一个空格。

## HTML 文本格式化

+ HTML 格式化标签
  + HTML 使用标签 <b>("bold") 与 <i>("italic") 对输出的文本进行格式, 如：粗体 or 斜体
  + 这些HTML标签被称为格式化标签（请查看底部完整标签参考手册）。
  + 通常标签 <strong> 替换加粗标签 <b> 来使用, <em> 替换 <i>标签使用。
  + 然而，这些标签的含义是不同的：
    + <b> 与<i> 定义粗体或斜体文本。
    + <strong> 或者 <em>意味着你要呈现的文本是重要的，所以要突出显示。现今所有主要浏览器都能渲染各种效果的字体。不过，未来浏览器可能会支持更好的渲染效果

+ HTML 文本格式化标签
  + <b>	        定义粗体文本
  + <em>	    定义着重文字
  + <i>	        定义斜体字
  + <small>	    定义小号字
  + <strong>	定义加重语气
  + <sub>	    定义下标字
  + <sup>	    定义上标字
  + <ins>	    定义插入字
  + <del>	    定义删除字

+ HTML "计算机输出" 标签
  + <code>	定义计算机代码
  + <kbd>	定义键盘码
  + <samp>	定义计算机代码样本
  + <var>	定义变量
  + <pre>	定义预格式文本

+ HTML 引文, 引用, 及标签定义
  + <abbr>	        定义缩写
  + <address>	    定义地址
  + <bdo>	        定义文字方向
  + <blockquote>	定义长的引用
  + <q>	            定义短的引用语
  + <cite>	        定义引用、引证
  + <dfn>	        定义一个定义项目。

## HTML 链接

+ HTML 使用超级链接与网络上的另一个文档相连。
+ HTML中的链接是一种用于在不同网页之间导航的元素。
+ 链接通常用于将一个网页与另一个网页或资源（如文档、图像、音频文件等）相关联。
+ 链接允许用户在浏览网页时单击文本或图像来跳转到其他位置，从而实现网页之间的互联。

+ HTML 超链接（链接）
  + HTML使用标签 <a> 来设置超文本链接。
  + 超链接可以是一个字，一个词，或者一组词，也可以是一幅图像，您可以点击这些内容来跳转到新的文档或者当前文档中的某个部分。
  + 当您把鼠标指针移动到网页中的某个链接上时，箭头会变为一只小手。
  + 在标签 <a> 中使用了 href 属性来描述链接的地址。
  + 默认情况下，链接将以以下形式出现在浏览器中：
    + 一个未访问过的链接显示为蓝色字体并带有下划线。
    + 访问过的链接显示为紫色并带有下划线。
    + 点击链接时，链接显示为红色并带有下划线。
  + 注意：如果为这些超链接设置了 CSS 样式，展示样式会根据 CSS 的设定而显示。

+ HTML 链接语法
  + 以下是 HTML 中创建链接的基本语法和属性：code><a> 元素：创建链接的主要HTML元素是<a>（锚）元素。<a>元素具有以下属性：
    + href：指定链接目标的URL，这是链接的最重要属性。可以是另一个网页的URL、文件的URL或其他资源的URL。
    + target（可选）：指定链接如何在浏览器中打开。常见的值包括 _blank（在新标签或窗口中打开链接）和 _self（在当前标签或窗口中打开链接）。
    + title（可选）：提供链接的额外信息，通常在鼠标悬停在链接上时显示为工具提示。
    + rel（可选）：指定与链接目标的关系，如 nofollow、noopener 等。
  + 链接的 HTML 代码很简单，它类似这样：
```html
<a href="url">链接文本</a>
<a href="https://www.runoob.com/">访问菜鸟教程</a>
```
  + href 属性描述了链接的目标。
  + 提示: "链接文本" 不必一定是文本。图片或其他 HTML 元素都可以成为链接。
  + 文本链接：最常见的链接类型是文本链接，它使用 <a> 元素将一段文本转化为可点击的链接，例如：
```html
<a href="https://www.example.com">访问示例网站</a>
```
  + 图像链接：您还可以使用图像作为链接。在这种情况下，<a> 元素包围着 <img> 元素。例如：
```html
<a href="https://www.example.com">
  <img src="example.jpg" alt="示例图片">
</a>
```
  + 锚点链接：除了链接到其他网页外，您还可以在同一页面内创建内部链接，这称为锚点链接。要创建锚点链接，需要在目标位置使用 <a> 元素定义一个标记，并使用#符号引用该标记。例如：
```html
<a href="#section2">跳转到第二部分</a>
<!-- 在页面中的某个位置 -->
<a name="section2"></a>
```
  + 下载链接：如果您希望链接用于下载文件而不是导航到另一个网页，可以使用 download 属性。例如：
```html
<a href="document.pdf" download>下载文档</a>
```

+ HTML 链接 - target 属性
  + 使用 target 属性，你可以定义被链接的文档在何处显示。
  + 下面的这行会在新窗口打开文档：
```html
<a href="https://www.runoob.com/" target="_blank" rel="noopener noreferrer">访问菜鸟教程!</a>
```

+ HTML 链接- id 属性
  + id 属性可用于创建一个 HTML 文档书签。
  + 提示: 书签不会以任何特殊方式显示，即在 HTML 页面中是不显示的，所以对于读者来说是隐藏的。

## HTML 头部

+ 使用 <title> 标签定义HTML文档的标题
+ 使用 <base> 定义页面中所有链接默认的链接目标地址。
+ 使用 <meta> 元素来描述HTML文档的描述，关键词，作者，字符集等。

+ HTML <head> 元素
  + <head> 元素包含了所有的头部标签元素。在 <head>元素中你可以插入脚本（scripts）, 样式文件（CSS），及各种meta信息。
  + 可以添加在头部区域的元素标签为: <title>, <style>, <meta>, <link>, <script>, <noscript> 和 <base>。

+ HTML <title> 元素
  + <title> 标签定义了不同文档的标题。
  + <title> 在 HTML/XHTML 文档中是必需的。
  + <title> 元素:
    + 定义了浏览器工具栏的标题
    + 当网页添加到收藏夹时，显示在收藏夹中的标题
    + 显示在搜索引擎结果页面的标题
  + 一个简单的 HTML 文档:
```html
<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8"> 
<title>文档标题</title>
</head>
 
<body>
文档内容......
</body>
 
</html>
```

+ HTML <base> 元素
  + <base> 标签描述了基本的链接地址/链接目标，该标签作为HTML文档中所有的链接标签的默认链接:
```html
<head>
<base href="http://www.runoob.com/images/" target="_blank">
</head>
```

+ HTML <link> 元素
  + <link> 标签定义了文档与外部资源之间的关系。
  + <link> 标签通常用于链接到样式表:
```html
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>
```

+ HTML <style> 元素
  + <style> 标签定义了HTML文档的样式文件引用地址.
  + 在<style> 元素中你也可以直接添加样式来渲染 HTML 文档:
```html
<head>
<style type="text/css">
body {
    background-color:yellow;
}
p {
    color:blue
}
</style>
</head>
```

+ HTML <meta> 元素
  + meta标签描述了一些基本的元数据。
  + <meta> 标签提供了元数据.元数据也不显示在页面上，但会被浏览器解析。
  + META 元素通常用于指定网页的描述，关键词，文件的最后修改时间，作者，和其他元数据。
  + 元数据可以使用于浏览器（如何显示内容或重新加载页面），搜索引擎（关键词），或其他Web服务。
  + <meta> 一般放置于 <head> 区域

+ <meta> 标签- 使用实例
  + 为搜索引擎定义关键词:
```html
<meta name="keywords" content="HTML, CSS, XML, XHTML, JavaScript">
```
  + 为网页定义描述内容:
```html
<meta name="description" content="免费 Web & 编程 教程">
```
  + 定义网页作者:
```html
<meta name="author" content="Runoob">
```
  + 每30秒钟刷新当前页面:
```html
<meta http-equiv="refresh" content="30">
```

+ HTML <script> 元素
  + <script> 标签用于加载脚本文件，如： JavaScript。
  + <script> 元素在以后的章节中会详细描述。

+ HTML head 元素
  + <head>	    定义了文档的信息
  + <title>	    定义了文档的标题
  + <base>	    定义了页面链接标签的默认链接地址
  + <link>	    定义了一个文档和外部资源之间的关系
  + <meta>	    定义了HTML文档中的元数据
  + <script>	定义了客户端的脚本文件
  + <style>	    定义了HTML文档的样式文件

## HTML 样式- CSS

+ CSS (Cascading Style Sheets) 用于渲染HTML元素标签的样式。

+ 如何使用CSS
  + CSS 是在 HTML 4 开始使用的,是为了更好的渲染HTML元素而引入的.
  + CSS 可以通过以下方式添加到HTML中:
    + 内联样式- 在HTML元素中使用"style" 属性
    + 内部样式表 -在HTML文档头部 <head> 区域使用<style> 元素 来包含CSS
    + 外部引用 - 使用外部 CSS 文件
  + 最好的方式是通过外部引用CSS文件.

+ 内联样式
  + 当特殊的样式需要应用到个别元素时，就可以使用内联样式。 使用内联样式的方法是在相关的标签中使用样式属性。样式属性可以包含任何 CSS 属性。以下实例显示出如何改变段落的颜色和左外边距。
```html
<p style="color:blue;margin-left:20px;">这是一个段落。</p>
```

+ HTML样式实例 - 背景颜色
  + 背景色属性（background-color）定义一个元素的背景颜色：
```html
<body style="background-color:yellow;">
<h2 style="background-color:red;">这是一个标题</h2>
<p style="background-color:green;">这是一个段落。</p>
</body>
```

+ HTML 样式实例 - 字体, 字体颜色 ，字体大小
  + 我们可以使用font-family（字体），color（颜色），和font-size（字体大小）属性来定义字体的样式:
```html
<h1 style="font-family:verdana;">一个标题</h1>
<p style="font-family:arial;color:red;font-size:20px;">一个段落。</p>
```
  + 现在通常使用font-family（字体），color（颜色），和font-size（字体大小）属性来定义文本样式，而不是使用<font>标签。

+ HTML 样式实例 - 文本对齐方式
  + 使用 text-align（文字对齐）属性指定文本的水平与垂直对齐方式：
```html
<h1 style="text-align:center;">居中对齐的标题</h1>
<p>这是一个段落。</p>
```
  + 文本对齐属性 text-align取代了旧标签 <center> 。

+ 内部样式表
  + 当单个文件需要特别样式时，就可以使用内部样式表。你可以在<head> 部分通过 <style>标签定义内部样式表:
```html
<head>
<style type="text/css">
body {background-color:yellow;}
p {color:blue;}
</style>
</head>
```

+ 外部样式表
  + 当样式需要被应用到很多页面的时候，外部样式表将是理想的选择。使用外部样式表，你就可以通过更改一个文件来改变整个站点的外观。
```html
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>
```

+ HTML 样式标签
  + <style>	定义文本样式
  + <link>	定义资源引用地址

## HTML 图像

+ HTML 图像- 图像标签（ <img>）和源属性（Src）
  + 在 HTML 中，图像由<img> 标签定义。
  + <img> 是空标签，意思是说，它只包含属性，并且没有闭合标签。
  + 要在页面上显示图像，你需要使用源属性（src）。src 指 "source"。源属性的值是图像的 URL 地址。
  + 定义图像的语法是：
```html
<img src="url" alt="some_text">
```
  + URL 指存储图像的位置。如果名为 "pulpit.jpg" 的图像位于 www.runoob.com 的 images 目录中，那么其 URL 为 http://www.runoob.com/images/pulpit.jpg。
  + 浏览器将图像显示在文档中图像标签出现的地方。如果你将图像标签置于两个段落之间，那么浏览器会首先显示第一个段落，然后显示图片，最后显示第二段。

+ HTML 图像- Alt属性
  + alt 属性用来为图像定义一串预备的可替换的文本。
  + 替换文本属性的值是用户定义的。
```html
<img src="boat.gif" alt="Big Boat">
```
  + 在浏览器无法载入图像时，替换文本属性告诉读者她们失去的信息。此时，浏览器将显示这个替代性的文本而不是图像。为页面上的图像都加上替换文本属性是个好习惯，这样有助于更好的显示信息，并且对于那些使用纯文本浏览器的人来说是非常有用的。

+ HTML 图像- 设置图像的高度与宽度
  + height（高度） 与 width（宽度）属性用于设置图像的高度与宽度。
  + 属性值默认单位为像素:
```html
<img src="pulpit.jpg" alt="Pulpit rock" width="304" height="228">
```
  + 提示: 指定图像的高度和宽度是一个很好的习惯。如果图像指定了高度宽度，页面加载时就会保留指定的尺寸。如果没有指定图片的大小，加载页面时有可能会破坏HTML页面的整体布局。

+ 基本的注意事项 - 有用的提示：
  + 注意: 假如某个 HTML 文件包含十个图像，那么为了正确显示这个页面，需要加载 11 个文件。加载图片是需要时间的，所以我们的建议是：慎用图片。
  + 注意: 加载页面时，要注意插入页面图像的路径，如果不能正确设置图像的位置，浏览器无法加载图片，图像标签就会显示一个破碎的图片。

+ HTML 图像标签
  + <img>	定义图像
  + <map>	定义图像地图
  + <area>	定义图像地图中的可点击区域

## HTML 表格

+ HTML 表格由 <table> 标签来定义。
+ HTML 表格是一种用于展示结构化数据的标记语言元素。
+ 每个表格均有若干行（由 <tr> 标签定义），每行被分割为若干单元格（由 <td> 标签定义），表格可以包含标题行（<th>）用于定义列的标题。
  + tr：tr 是 table row 的缩写，表示表格的一行。
  + td：td 是 table data 的缩写，表示表格的数据单元格。
  + th：th 是 table header的缩写，表示表格的表头单元格。
+ 数据单元格可以包含文本、图片、列表、段落、表单、水平线、表格等等。

+ <thead > 用于定义表格的标题部分: 在 <thead > 中，使用 <th > 元素定义列的标题，以上实例中列标题分别为"列标题1"，"列标题2"和"列标题3"。
+ <tbody > 用于定义表格的主体部分: 在 <tbody > 中，使用 <tr > 元素定义行，并在每行中使用 <td > 元素定义单元格数据，以上实例中有两行数据，每行包含三个单元格。
+ 通过使用 <th > 元素定义列标题，可以使其在表格中以粗体显示，与普通单元格区分开来。
+ HTML 表格还可以具有其他部分，如 <tfoot > （表格页脚）和 <caption > （表格标题），<tfoot > 可用于在表格的底部定义摘要、统计信息等内容。 <caption > 可用于为整个表格定义标题。
+ HTML 表格还支持合并单元格和跨行/跨列的操作，以及其他样式和属性的应用，以满足各种需求。
+ 我们也可以使用 CSS 来进一步自定义表格的样式和外观。

+ HTML 表格和边框属性

+ 如果不定义边框属性，表格将不显示边框。有时这很有用，但是大多数时候，我们希望显示边框。
+ 使用边框属性来显示一个带有边框的表格：
```html
<table border="1">
    <tr>
        <td>Row 1, cell 1</td>
        <td>Row 1, cell 2</td>
    </tr>
</table>
```

+ HTML 表格表头
  + 表格的表头使用 <th> 标签进行定义。
  + 大多数浏览器会把表头显示为粗体居中的文本：

+ HTML 表格标签
  + <table>	    定义表格
  + <th>	    定义表格的表头
  + <tr>	    定义表格的行
  + <td>	    定义表格单元
  + <caption>	定义表格标题
  + <colgroup>	定义表格列的组
  + <col>	    定义用于表格列的属性
  + <thead>	    定义表格的页眉
  + <tbody>	    定义表格的主体
  + <tfoot>	    定义表格的页脚