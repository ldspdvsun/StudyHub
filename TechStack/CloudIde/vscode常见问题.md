## Vscode中Python代码引入其他模块下自定义包


+ 在 VS Code 中导入其他文件夹下的模块，需要使用 Python 的模块搜索路径，可以通过以下步骤实现：

假设我们的项目结构如下：

```sh
my_project/
├── main.py
└── utils/
    ├── __init__.py
    └── my_module.py
```

   1. 在自定义的文件夹中创建一个 __init__.py 文件，使该文件夹变成一个包。

   2. 在需要导入模块的 Python 文件中，使用 sys.path.append() 方法将自定义文件夹所在的路径添加到模块搜索路径中。使用 import 语句导入自定义文件夹下的模块即可。

   例如，现在我们需要在 main.py 中导入 my_module.py

   main.py
   ```py
   import sys
   sys.path.append('utils')  # 将 utils 文件夹添加到模块搜索路径中
   import my_module  # 导入自定义模块
   ```


+ 如果导入其他项目文件夹中的模块，但是需要将其他项目文件夹所在的路径添加到 Python 的模块搜索路径中。

假设我们有两个项目：project1 和 project2，它们的文件结构如下：

```sh
project1/
├── main.py
└── utils/
    ├── __init__.py
    └── my_module.py

project2/
├── main.py
└── helpers/
    ├── __init__.py
    └── helper_module.py
```

现在，我们需要在 project1/main.py 中导入 project2/helpers/helper_module.py 中的模块，可以按照以下步骤操作：

1. 在 project1/main.py 文件中添加以下代码，将 project2 文件夹所在的路径添加到 Python 的模块搜索路径中：

```py
import sys
sys.path.append('../project2')  # 将 project2 文件夹添加到模块搜索路径中
然后可以使用 import 语句导入 project2/helpers/helper_module.py 中的模块了：
from helpers.helper_module import some_function
```

2. 这样就可以在 project1/main.py 中使用 some_function 函数了。

需要注意的是，如果多个项目之间存在相互依赖的情况，最好使用包管理工具（如 pipenv 或者 poetry）来管理项目依赖，而不是手动添加模块搜索路径。


## code-runner使用

### 如何禁止不必要的输出

您可以按照以下步骤在 VSCode 中的设置中进行配置：

1. 打开 VSCode，点击左侧的菜单栏中的“文件(File)”菜单，选择“首选项(Preferences)”下的“设置(Settings)”选项。

2. 在搜索框中输入“code-runner”，找到“Code-runner: Run In Terminal”这一项，将其设置为“true”。（不勾选）

3. 在设置中搜索“Code-runner: Clear Previous Output”，表示运行代码前清空之前的输出。（勾选）

4. 保存设置后，再次使用 Code-runner 运行代码，就应该只保留正常输出了。

### 如何引入自定义的头文件

在c语言编译的时候加入 -I 头文件所在目录 即可，以下是code-runner的配置

```json
{
    "liveServer.settings.donotShowInfoMsg": true,
    "editor.guides.bracketPairs": true,
    "settingsSync.ignoredSettings": [],
    "C_Cpp.autocompleteAddParentheses": true,
    "explorer.confirmDragAndDrop": false,
    "workbench.editorAssociations": {
        "*.drawio": "default"
    },
    "hediet.vscode-drawio.codeLinkActivated": true,
    "C_Cpp.files.exclude": {
        "**/.vscode": true,
        "**/.vs": true
    },
    "workbench.tree.indent": 16,
    "debug.onTaskErrors": "showErrors",
    "code-runner.executorMap": {
        "javascript": "node",
        "java": "cd $dir && javac $fileName && java $fileNameWithoutExt",
        "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt.out -I /root/code/vscode-server/7714/SMY/include -I /root/code/vscode-server/posixtestsuite/include && $dir$fileNameWithoutExt.out",
        "zig": "zig run",
        "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
        "objective-c": "cd $dir && gcc -framework Cocoa $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
        "php": "php",
        "python": "set PYTHONIOENCODING=utf-8 && set PYTHONPATH=. && python -u",
        "perl": "perl",
        "perl6": "perl6",
        "ruby": "ruby",
        "go": "go run",
        "lua": "lua",
        "groovy": "groovy",
        "powershell": "powershell -ExecutionPolicy ByPass -File",
        "bat": "cmd /c",
        "shellscript": "bash",
        "fsharp": "fsi",
        "csharp": "scriptcs",
        "vbscript": "cscript //Nologo",
        "typescript": "ts-node",
        "coffeescript": "coffee",
        "scala": "scala",
        "swift": "swift",
        "julia": "julia",
        "crystal": "crystal",
        "ocaml": "ocaml",
        "r": "Rscript",
        "applescript": "osascript",
        "clojure": "lein exec",
        "haxe": "haxe --cwd $dirWithoutTrailingSlash --run $fileNameWithoutExt",
        "rust": "cd $dir && rustc $fileName && $dir$fileNameWithoutExt",
        "racket": "racket",
        "scheme": "csi -script",
        "ahk": "autohotkey",
        "autoit": "autoit3",
        "dart": "dart",
        "pascal": "cd $dir && fpc $fileName && $dir$fileNameWithoutExt",
        "d": "cd $dir && dmd $fileName && $dir$fileNameWithoutExt",
        "haskell": "runghc",
        "nim": "nim compile --verbosity:0 --hints:off --run",
        "lisp": "sbcl --script",
        "kit": "kitc --run",
        "v": "v run",
        "sass": "sass --style expanded",
        "scss": "scss --style expanded",
        "less": "cd $dir && lessc $fileName $fileNameWithoutExt.css",
        "FortranFreeForm": "cd $dir && gfortran $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
        "fortran-modern": "cd $dir && gfortran $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
        "fortran_fixed-form": "cd $dir && gfortran $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
        "fortran": "cd $dir && gfortran $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
        "sml": "cd $dir && sml $fileName",
    },
    "[python]": {
        "editor.formatOnType": true,
        "editor.defaultFormatter": "ms-python.python"
    },
    "terminal.integrated.env.osx": {
        "PYTHONPATH": "${workspaceFolder}/",
    },
    "terminal.integrated.env.linux": {
        "PYTHONPATH": "${workspaceFolder}/",
    },
    "terminal.integrated.env.windows": {
        "PYTHONPATH": "${workspaceFolder}/",
    },
    "env": {
        "PYTHONPATH": "${workspaceRoot}"
    },
    "code-runner.fileDirectoryAsCwd": true,
    "workbench.startupEditor": "none",
    "window.menuBarVisibility": "classic",
    "leetcode.outputFolder": "$difficulty",
    "leetcode.filePath": {
        "default": {
            "folder": "",
            "filename": "${id}.${kebab-case-name}.${ext}"
        }
    },
    "leetcode.endpoint": "leetcode-cn",
    "markdown.preview.breaks": true,
    "leetcode.workspaceFolder": "/root/.leetcode",
    "leetcode.showDescription": "Both",
    "leetcode.hint.configWebviewMarkdown": false,
    "python.autoComplete.extraPaths": [],
    "python.analysis.extraPaths": [],
    "workbench.editor.enablePreview": false,
    "explorer.autoReveal": "focusNoScroll",
    "workbench.colorTheme": "Learn with Sumit Official Theme",
    "code-runner.saveAllFilesBeforeRun": true,
    "code-runner.showStopIconInEditorTitleMenu": false,
    "code-runner.saveFileBeforeRun": true,
    "code-runner.showExecutionMessage": false,
    "code-runner.clearPreviousOutput": true,
}
```