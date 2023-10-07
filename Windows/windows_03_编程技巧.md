## 简介

+ windows系统下常用的编程技巧

## windows cmd 创建文件

在Windows的命令提示符（CMD）中，您可以使用`echo`命令创建文本文件，也可以使用`copy con`命令手动输入文本内容并保存为文件。以下是一些示例：

1. 使用`echo`命令创建文本文件：

   ```
   echo Hello, World! > filename.txt
   ```

   这将创建一个名为`filename.txt`的文本文件，并将内容"Hello, World!"写入其中。如果文件已经存在，它将被覆盖。

2. 使用`copy con`命令手动输入文本内容并保存为文件：

   ```
   copy con filename.txt
   ```

   然后，您可以输入文本内容，按Enter键，然后按`Ctrl + Z`组合键，然后再按Enter键来保存文件。这将创建一个名为`filename.txt`的文本文件，您可以在其中输入您想要的文本内容。

3. 使用Notepad命令创建和编辑文本文件：

   ```
   notepad filename.txt
   ```

   这将打开记事本文本编辑器，您可以在其中创建和编辑文本文件。保存文件后，关闭记事本即可。

请注意，以上示例中的`filename.txt`可以替换为您想要的文件名和扩展名。您可以使用适当的文件路径来指定文件的位置。