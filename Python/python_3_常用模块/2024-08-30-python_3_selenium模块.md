---
category: Python
date: 2024-08-30 09:00:00 +0800
layout: post
title: python_3_selenium模块
tag: Python
---
## 简介

+ python3中selenium模块相关笔记

## python3 selenium模块 详解

`Selenium` 是一个流行的 Web 测试和自动化工具，通常用于通过编程方式控制浏览器执行各种任务。`Selenium` 提供了多种语言绑定，其中之一是 Python。通过 `selenium` 模块，你可以用 Python 编写脚本来自动化浏览器的操作，如填表、点击按钮、抓取数据等。

下面是 `Selenium` 模块的详细介绍，包括安装、基本用法以及常用功能。

### 1. 安装 `Selenium`
要在 Python 中使用 `Selenium`，首先需要安装它：

```bash
pip install selenium
```

### 2. 基本用法
在使用 `Selenium` 之前，你还需要下载一个适用于你所用浏览器的 WebDriver。例如，如果你使用 Chrome 浏览器，你需要下载 ChromeDriver。

#### 2.1 导入模块并设置 WebDriver

```python
from selenium import webdriver

# 设置 Chrome WebDriver 的路径
driver = webdriver.Chrome(executable_path='/path/to/chromedriver')

# 打开一个网页
driver.get('https://www.example.com')
```

#### 2.2 查找元素
`Selenium` 提供多种方法来查找页面中的元素：

- `find_element_by_id(id)`
- `find_element_by_name(name)`
- `find_element_by_xpath(xpath)`
- `find_element_by_css_selector(css_selector)`
- `find_element_by_tag_name(tag_name)`
- `find_element_by_class_name(class_name)`

```python
# 查找元素
element = driver.find_element_by_id('element_id')

# 对元素进行操作
element.click()  # 点击元素
element.send_keys('text')  # 输入文本
```

#### 2.3 与页面交互

- **点击按钮：**

```python
button = driver.find_element_by_xpath('//button[@id="submit"]')
button.click()
```

- **输入文本：**

```python
input_box = driver.find_element_by_name('q')
input_box.send_keys('Selenium Python')
```

- **获取文本内容：**

```python
text = driver.find_element_by_tag_name('h1').text
print(text)
```

### 3. 常用功能

#### 3.1 等待页面加载
有时页面元素需要时间加载，`Selenium` 提供了两种等待机制：

- **隐式等待：** 在设置的时间内等待元素加载完成。

```python
driver.implicitly_wait(10)  # 等待最多10秒
```

- **显式等待：** 明确等待某个条件满足。

```python
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

element = WebDriverWait(driver, 10).until(
    EC.presence_of_element_located((By.ID, 'myElement'))
)
```

#### 3.2 处理弹窗
可以用 `switch_to.alert` 来处理 JavaScript 弹窗：

```python
alert = driver.switch_to.alert
alert.accept()  # 接受弹窗
alert.dismiss()  # 关闭弹窗
```

#### 3.3 处理多窗口
`Selenium` 允许在多个窗口或标签页之间切换：

```python
# 获取当前窗口句柄
main_window = driver.current_window_handle

# 获取所有窗口句柄
windows = driver.window_handles

# 切换到新窗口
driver.switch_to.window(windows[1])
```

#### 3.4 截图
可以用 `save_screenshot` 方法截图：

```python
driver.save_screenshot('screenshot.png')
```

### 4. 关闭浏览器
完成操作后，应该关闭浏览器：

```python
driver.quit()
```

### 5. 完整示例
以下是一个完整的示例，展示如何使用 `Selenium` 进行简单的搜索操作：

```python
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

# 设置 WebDriver
driver = webdriver.Chrome(executable_path='/path/to/chromedriver')

# 打开 Google
driver.get('https://www.google.com')

# 查找搜索框并输入内容
search_box = driver.find_element_by_name('q')
search_box.send_keys('Selenium Python')
search_box.send_keys(Keys.RETURN)

# 等待搜索结果页面加载并获取结果
driver.implicitly_wait(10)
results = driver.find_elements_by_xpath('//h3')

for result in results:
    print(result.text)

# 关闭浏览器
driver.quit()
```

### 6. 高级功能
`Selenium` 还支持处理复杂的场景，如文件上传、拖放、iframe 操作等。了解这些功能可以通过官方文档或其他高级教程。

### 7. 参考文档
你可以在 [Selenium 官方文档](https://www.selenium.dev/documentation/) 中找到更多详细的内容和使用示例。

## python3 selenium.WebDriver类 详解

`WebDriver` 类是 Selenium 中的核心类之一，用于控制和与浏览器交互。通过 `WebDriver` 类，您可以启动和操作各种浏览器（如 Chrome、Firefox、Safari 等），执行诸如打开网页、查找元素、模拟用户输入、点击、截屏等操作。

以下是 `WebDriver` 类的详细解释：

### 1. `WebDriver` 类简介

`WebDriver` 是一个抽象类，用于定义所有浏览器驱动程序（如 `ChromeDriver`、`FirefoxDriver` 等）必须实现的接口。通过 `WebDriver` 类，可以执行一系列浏览器操作，如导航、窗口管理、页面交互等。

### 2. 浏览器驱动初始化

使用 `WebDriver` 类时，通常需要实例化一个特定浏览器的驱动程序。以下是几个常见的浏览器驱动初始化方式：

```python
from selenium import webdriver

# 初始化 Chrome 浏览器驱动
driver = webdriver.Chrome()

# 初始化 Firefox 浏览器驱动
driver = webdriver.Firefox()

# 初始化 Safari 浏览器驱动
driver = webdriver.Safari()

# 初始化 Edge 浏览器驱动
driver = webdriver.Edge()
```

### 3. 常用方法与属性

`WebDriver` 类提供了许多方法和属性，用于控制和操作浏览器。以下是一些常用的方法和属性：

#### 3.1 页面导航

- **`get(url)`**: 导航到指定的 URL。

  ```python
  driver.get("https://www.example.com")
  ```

- **`current_url`**: 返回当前页面的 URL。

  ```python
  current_page_url = driver.current_url
  ```

- **`title`**: 返回当前页面的标题。

  ```python
  page_title = driver.title
  ```

- **`back()`**: 模拟浏览器的后退按钮。

  ```python
  driver.back()
  ```

- **`forward()`**: 模拟浏览器的前进按钮。

  ```python
  driver.forward()
  ```

- **`refresh()`**: 刷新当前页面。

  ```python
  driver.refresh()
  ```

#### 3.2 元素查找

- **`find_element_by_id(id)`**: 根据元素的 `id` 查找元素。

  ```python
  element = driver.find_element_by_id("element-id")
  ```

- **`find_element_by_name(name)`**: 根据元素的 `name` 属性查找元素。

  ```python
  element = driver.find_element_by_name("element-name")
  ```

- **`find_element_by_xpath(xpath)`**: 根据 XPath 表达式查找元素。

  ```python
  element = driver.find_element_by_xpath("//div[@class='example']")
  ```

- **`find_element_by_css_selector(selector)`**: 根据 CSS 选择器查找元素。

  ```python
  element = driver.find_element_by_css_selector(".example-class")
  ```

- **`find_elements_by_*`**: 对应于 `find_element_by_*` 的方法，用于查找多个符合条件的元素，返回一个元素列表。

#### 3.3 浏览器窗口管理

- **`maximize_window()`**: 最大化浏览器窗口。

  ```python
  driver.maximize_window()
  ```

- **`minimize_window()`**: 最小化浏览器窗口。

  ```python
  driver.minimize_window()
  ```

- **`set_window_size(width, height)`**: 设置浏览器窗口大小。

  ```python
  driver.set_window_size(1024, 768)
  ```

- **`get_window_size()`**: 获取当前窗口大小。

  ```python
  size = driver.get_window_size()
  ```

- **`switch_to.window(window_name)`**: 切换到指定的窗口或标签页。

  ```python
  driver.switch_to.window(driver.window_handles[1])
  ```

#### 3.4 框架和窗口切换

- **`switch_to.frame(frame_reference)`**: 切换到指定的 iframe 或 frame。

  ```python
  driver.switch_to.frame("frame-name")
  ```

- **`switch_to.default_content()`**: 退出 iframe 或 frame，返回到主页面内容。

  ```python
  driver.switch_to.default_content()
  ```

#### 3.5 警告和弹出框处理

- **`switch_to.alert`**: 切换到浏览器警告对话框（alert）。

  ```python
  alert = driver.switch_to.alert
  alert.accept()  # 确认警告
  alert.dismiss()  # 取消警告
  ```

#### 3.6 执行 JavaScript

- **`execute_script(script, *args)`**: 在页面上执行 JavaScript 脚本。

  ```python
  driver.execute_script("alert('Hello, world!')")
  ```

#### 3.7 截屏

- **`save_screenshot(filename)`**: 截取当前窗口并保存为文件。

  ```python
  driver.save_screenshot("screenshot.png")
  ```

### 4. 关闭与退出

- **`close()`**: 关闭当前窗口。如果这是唯一的窗口，则会退出 WebDriver 会话。

  ```python
  driver.close()
  ```

- **`quit()`**: 关闭所有关联的窗口，并退出 WebDriver 会话。

  ```python
  driver.quit()
  ```

### 5. 等待

在 WebDriver 中，等待是一个非常重要的概念，尤其是在处理动态加载的网页内容时。Selenium 提供了两种等待方式：

#### 5.1 隐式等待

设置一个全局等待时间，WebDriver 会在查找元素时，轮询等待元素在指定时间内加载完成。

```python
driver.implicitly_wait(10)  # 等待最多10秒
```

#### 5.2 显式等待

显式等待指定某个条件，在指定时间内等待该条件满足。如果条件在超时时间内满足，继续执行；否则抛出异常。

```python
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

element = WebDriverWait(driver, 10).until(
    EC.presence_of_element_located((By.ID, "element-id"))
)
```

### 6. 异常处理

使用 `WebDriver` 时，可能会遇到各种异常，如元素未找到、超时、无效的 URL 等。Selenium 提供了一些常见的异常类：

- `NoSuchElementException`: 元素未找到。
- `TimeoutException`: 操作超时。
- `WebDriverException`: 一般性的 WebDriver 错误。

可以通过异常处理机制来捕获和处理这些错误。

```python
from selenium.common.exceptions import NoSuchElementException

try:
    driver.find_element_by_id("non-existent-id")
except NoSuchElementException:
    print("Element not found!")
```

### 7. 示例代码

以下是一个简单的示例，展示了如何使用 `WebDriver` 类打开网页、查找元素并与之交互。

```python
from selenium import webdriver

# 初始化 Chrome 浏览器
driver = webdriver.Chrome()

# 打开网页
driver.get("https://www.example.com")

# 查找元素并与之交互
search_box = driver.find_element_by_name("q")
search_box.send_keys("Selenium WebDriver")
search_box.submit()

# 等待页面加载完成
driver.implicitly_wait(5)

# 获取页面标题
print(driver.title)

# 关闭浏览器
driver.quit()
```

### 总结

`WebDriver` 类是 Selenium 的核心，提供了丰富的功能来自动化浏览器操作。掌握 `WebDriver` 的各种方法和属性，是进行 Web 自动化测试的基础。

## python3 WebDriver.get()函数 详解

`WebDriver.get()` 是 Selenium WebDriver 的一个函数，用于让 WebDriver 导航到指定的 URL（即加载网页）。该函数是自动化浏览器操作的基础之一。以下是 `WebDriver.get()` 函数的详细说明：

### 1. 函数定义

```python
webdriver.get(url)
```

- `webdriver` 是你初始化的浏览器对象（例如 Chrome、Firefox 等）。
- `url` 是你希望 WebDriver 加载的网页的 URL，它必须是一个字符串。

### 2. 参数说明

- **url**: 这是一个字符串，表示你想让 WebDriver 打开的网页地址。该 URL 必须以 `http://` 或 `https://` 开头。如果没有指定协议，WebDriver 将不会加载页面，并且可能抛出异常。

### 3. 返回值

- 该方法没有返回值。WebDriver 将会打开指定的 URL，并在页面完全加载后继续执行后续代码。

### 4. 常见用途

- **打开网页**: 这是 `WebDriver.get()` 最常见的用途，用于在浏览器中导航到特定的网页。

  ```python
  from selenium import webdriver
  
  # 初始化 WebDriver
  driver = webdriver.Chrome()
  
  # 打开网页
  driver.get("https://www.example.com")
  ```

- **与其他 WebDriver 操作结合**: 在加载页面后，通常会执行其他操作，如查找元素、执行 JavaScript 等。

  ```python
  from selenium import webdriver
  
  driver = webdriver.Chrome()
  driver.get("https://www.example.com")
  
  # 查找页面中的元素
  element = driver.find_element_by_id("example-id")
  
  # 执行其他操作
  element.click()
  ```

### 5. 注意事项

- **等待页面加载**: `WebDriver.get()` 会等待页面的完全加载，即等待所有同步加载的资源（HTML、CSS、JavaScript 等）都加载完成后，才会继续执行下一行代码。但是，某些动态内容（例如通过 AJAX 加载的数据）可能需要手动等待。

  ```python
  from selenium.webdriver.support.ui import WebDriverWait
  from selenium.webdriver.support import expected_conditions as EC
  
  driver.get("https://www.example.com")
  
  # 等待某个元素加载完成
  WebDriverWait(driver, 10).until(
      EC.presence_of_element_located(("id", "example-id"))
  )
  ```

- **异常处理**: 如果给定的 URL 格式不正确，或由于其他原因无法加载页面，WebDriver 可能会抛出异常（如 `WebDriverException`）。在实际应用中，可以通过异常处理机制捕获并处理这些错误。

  ```python
  try:
      driver.get("invalid-url")
  except Exception as e:
      print(f"An error occurred: {e}")
  ```

### 6. 关闭 WebDriver

在使用完 WebDriver 后，应该调用 `quit()` 方法来关闭浏览器并释放资源。

```python
driver.quit()
```

### 总结

`WebDriver.get()` 是 Selenium WebDriver 中非常基本且重要的函数，用于导航到指定网页。理解和正确使用这个方法，是自动化浏览器操作的基础。

## python3 WebDriver.delete_all_cookies()函数 详解

`WebDriver.delete_all_cookies()` 是 Selenium WebDriver 中的一个函数，用于删除当前会话中的所有 cookies。下面是对该函数的详细解释：

### 功能
`delete_all_cookies()` 方法的主要功能是在自动化测试过程中清除浏览器中所有的 cookies。Cookies 是存储在浏览器中的小数据文件，通常用于保持用户登录状态、存储用户偏好等。在某些测试场景中，可能需要删除这些 cookies 以确保测试的独立性和一致性。

### 用法

```python
from selenium import webdriver

# 创建 WebDriver 实例
driver = webdriver.Chrome()

# 打开某个网页
driver.get("https://www.example.com")

# 删除所有 cookies
driver.delete_all_cookies()

# 继续执行其他操作
```

### 应用场景
- **清除会话数据**: 当你希望从一个干净的状态开始测试时，可以使用 `delete_all_cookies()` 来清除所有的 session 信息。
- **模拟不同用户登录**: 在测试不同用户登录时，删除 cookies 可以防止前一个用户的会话信息干扰到下一个用户。
- **重置浏览器状态**: 在多步骤的测试中，删除 cookies 可以帮助重置浏览器状态，以确保每个步骤都从同一初始状态开始。

### 注意事项
- 这个方法会删除当前会话的所有 cookies，并且在调用 `delete_all_cookies()` 之后，如果页面依赖 cookies 工作，可能需要重新加载页面或者重新设置 cookies。
- 删除 cookies 不会影响浏览器的历史记录或缓存，只会影响 cookies。

### 常见问题
- **删除后无效**: 如果删除 cookies 后仍然看到之前的数据，可能是因为浏览器的缓存问题，建议同时清除缓存。
- **权限问题**: 某些 cookies 可能由于安全设置而无法删除，这通常涉及到跨域或安全标志的 cookies。

通过使用 `delete_all_cookies()`，你可以确保在不同的测试场景中拥有一个干净的环境，从而提高测试的准确性和可靠性。

## python3 WebDriver.find_elements()函数 详解

`WebDriver.find_elements()` 是 Selenium WebDriver 中用于查找网页元素的一个函数。它返回符合特定定位策略的所有元素列表。如果没有找到任何元素，则返回空列表。

### 函数签名
```python
elements = driver.find_elements(by=By.XPATH, value="//tag[@attribute='value']")
```

### 参数
- `by`: 用于指定查找元素的方式，通常使用 `By` 类提供的常量，例如 `By.ID`, `By.NAME`, `By.XPATH` 等。
- `value`: 一个字符串，指定如何根据 `by` 参数查找元素的值。例如，如果 `by=By.ID`，那么 `value` 就是对应的元素 `id` 值。

### 常用的 `By` 定位方式
- `By.ID`: 通过元素的 `id` 属性定位元素。
- `By.NAME`: 通过元素的 `name` 属性定位元素。
- `By.CLASS_NAME`: 通过元素的 `class` 属性定位元素。
- `By.TAG_NAME`: 通过元素的标签名定位元素。
- `By.LINK_TEXT`: 通过元素的文本内容（超链接）定位元素。
- `By.PARTIAL_LINK_TEXT`: 通过部分文本内容定位超链接。
- `By.XPATH`: 通过 XPath 表达式定位元素。
- `By.CSS_SELECTOR`: 通过 CSS 选择器定位元素。

### 返回值
- `List[WebElement]`: 由所有匹配元素组成的列表。如果没有找到元素，返回空列表。

### 示例代码
```python
from selenium import webdriver
from selenium.webdriver.common.by import By

# 初始化 WebDriver（比如使用 Chrome 浏览器）
driver = webdriver.Chrome()

# 打开一个网址
driver.get("https://www.example.com")

# 使用 find_elements() 查找元素列表
elements = driver.find_elements(By.CLASS_NAME, "example-class")

# 遍历并操作元素
for element in elements:
    print(element.text)

# 关闭 WebDriver
driver.quit()
```

### 注意事项
- 与 `find_element()` 不同，`find_elements()` 不会抛出 `NoSuchElementException` 异常。如果没有找到元素，返回的是一个空列表。
- `find_elements()` 查找所有符合条件的元素，而 `find_element()` 仅返回第一个匹配的元素。

通过 `find_elements()`，可以轻松地处理网页中的多个相似元素，比如同一类的按钮、表单元素等。