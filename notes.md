<center><font size=7>Notes</font></center>
<p align='right'>by Nemo</p>
<p align='right'>2023.9.24</p>

# 前言
此篇笔记将基于一本叫做Pro Git的书，简短讲述git的使用。  
## 学习资源
- [Pro Git](https://git-scm.com/book/en/v2)  /  [Pro Git中文版](https://git-scm.com/book/zh/v2)，推荐阅读1-5章
- [ohshitgit](https://ohshitgit.com/)，简短的介绍了如何从 Git 错误中恢复
- [Git for Computer Scientists](https://eagain.net/articles/git-for-computer-scientists/)，简短的介绍了 Git 的数据模型
- [git-from-the-bottom-up](https://jwiegley.github.io/git-from-the-bottom-up/)，详细的介绍了 Git 的实现细节
- [explain-git-in-simple-words](https://xosh.org/explain-git-in-simple-words/)，如其名
- [学习git的在线游戏](https://learngitbranching.js.org/)，挺好玩的
- [用动图展示10大Git命令](https://zhuanlan.zhihu.com/p/132573100)，一篇精美文章


## 我们为什么需要git
git是一个分布式版本控制软件  
在项目开发中，它能方便我们跟踪文件的信息，包括谁修改了它、变化了哪些部分；可以让我们更方便地添加、调试新功能，如果不行还可以回退到上一个版本；可以让我们更加方便地团队协作，和其他人进行信息交互，加快工作效率  
世界上最大的开源代码社区github就是基于git的  
从短期好处来看，学习git可以方便你进行代码的管理、调试，从长远角度来看，将来你一定会和别人协同工作，那么学会使用git很可能是一个必不可少的技能  

## 该如何学git
我分享一下我的看法：git的功能实在是太多了，想一口气掌握所有的功能实在是不可能。  
我的建议是可以先掌握基本的用法，在实践中再慢慢摸索。我是通过[学习git的在线游戏](https://learngitbranching.js.org/)上手git的  
[Pro Git](https://git-scm.com/book/en/v2)  /  [Pro Git中文版](https://git-scm.com/book/zh/v2)电子书详尽介绍了git的使用，可以把它作为可以时常翻阅的手册，如果你愿意看官方文档可以直接`git help <command> / git <command> --help`，简短用法的查看可以`git <command> -h`  
结合代码托管网站使用（比如github）。拥有一个属于自己的代码仓库，可以放置你的课程项目或者大作业、你的一些新奇的有趣的想法，这不是一件令人激动的事吗？更进一步，你还可以查看别人的项目，在`issue`栏与来自世界各地的开发者参与讨论，感兴趣可以`fork`别人的项目然后添加新的功能，在与项目拥有者的交流中成为朋友，这也是一件美事。  
如果你也是一名开源爱好者，那么就开始吧。

# 起步
## 下载和安装
[git下载](https://git-scm.com/download/win)，或者自行上网找博客

## git配置
使用`git config`的工具来帮助设置控制 Git 外观和行为的配置变量。这些变量存储在三个不同的位置：
1. /etc/gitconfig 文件: 包含系统上每一个用户及他们仓库的通用配置。 如果在执行 git config 时带上--system 选项，那么它就会读写该文件中的配置变量
2. ~/.gitconfig 或 ~/.config/git/config 文件：只针对当前用户。 你可以传递 --global 选项让 Git
读写此文件，这会对你系统上 __所有__ 的仓库生效
3. 当前使用仓库的 Git 目录中的 config 文件（即 .git/config）：针对该仓库。 你可以传递 --local 选项让 Git 强制读写此文件，默认情况下用的就是它。

每一级别会覆盖上一级别的配置

# intro
## 分布式版本控制系统
在这类系统中，客户端并不只提取最新版本的文件快照， 而是把代码仓库完整地镜像下来，包括完整的历史记录。 这么一来，任何一处协同工作用的服务器发生故障，事后都可以用任何一个镜像出来的本地仓库恢复。 因为每一次的克隆操作，实际上都是一次对代码仓库的完整备份。


SHA-1 哈希
Git 有三种状态，你的文件可能
处于其中之一： 已提交（committed）、已修改（modified） 和 已暂存（staged）
• 已修改表示修改了文件，但还没保存到数据库中。
• 已暂存表示对一个已修改文件的当前版本做了标记，使之包含在下次提交的快照中。
• 已提交表示数据已经安全地保存在本地数据库中


Git 前的配置
/etc/gitconfig 文件: 包含系统上每一个用户及他们仓库的通用配置。 如果在执行 git config 时带上
--system 选项，那么它就会读写该文件中的配置变量。 （由于它是系统配置文件，因此你需要管理员或
超级用户权限来修改它。）
2. ~/.gitconfig 或 ~/.config/git/config 文件：只针对当前用户。 你可以传递 --global 选项让 Git
读写此文件，这会对你系统上 所有 的仓库生效。
3. 当前使用仓库的 Git 目录中的 config 文件（即 .git/config）：针对该仓库。 你可以传递 --local 选
项让 Git 强制读写此文件，虽然默认情况下用的就是它。。 （当然，你需要进入某个 Git 仓库中才能让该选
项生效。）


请记住，你工作目录下的每一个文件都不外乎这两种状态：已跟踪 或 未跟踪。 已跟踪的文件是指那些被纳入了
版本控制的文件，在上一次快照中有它们的记录，在工作一段时间后， 它们的状态可能是未修改，已修改或已
30
放入暂存区。简而言之，已跟踪的文件就是 Git 已经知道的文件




D:\learning\git>git status
On branch master
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        notes.md
        progit.pdf

nothing added to commit but untracked files present (use "git add" to track)

git status

使用命令 git add 开始跟踪一个文件


暂存已修改的文件
现在我们来修改一个已被跟踪的文件。 如果你修改了一个名为 CONTRIBUTING.md 的已被跟踪的文件，然后运
行 git status 命令，会看到下面内容：

需要运行 git add 命令。 这是个多功能命令：可以用它开
始跟踪新文件，或者把已跟踪的文件放到暂存区，还能用于合并时把有冲突的文件标记为已解决状态等

状态简览
git status -s 

忽略文件
一般我们总会有些文件无需纳入 Git 的管理，也不希望它们总出现在未跟踪文件列表。 通常都是些自动生成的文
件，比如日志文件，或者编译过程中创建的临时文件等。 在这种情况下，我们可以创建一个名为 .gitignore
的文件，列出要忽略的文件的模式。

文件 .gitignore 的格式规范如下：
• 所有空行或者以 # 开头的行都会被 Git 忽略。
• 可以使用标准的 glob 模式匹配，它会递归地应用在整个工作区中。
• 匹配模式可以以（/）开头防止递归。
• 匹配模式可以以（/）结尾指定目录。
• 要忽略指定模式以外的文件或目录，可以在模式前加上叹号（!）取反。
所谓的 glob 模式是指 shell 所使用的简化了的正则表达式。 星号（*）匹配零个或多个任意字符；[abc] 匹配
任何一个列在方括号中的字符 （这个例子要么匹配一个 a，要么匹配一个 b，要么匹配一个 c）； 问号（?）只
匹配一个任意字符；如果在方括号中使用短划线分隔两个字符， 表示所有在这两个字符范围内的都可以匹配
（比如 [0-9] 表示匹配所有 0 到 9 的数字）。 使用两个星号（**）表示匹配任意中间目录，比如 a/**/z 可以
匹配 a/z 、 a/b/z 或 a/b/c/z 等。


![Alt text](image.png)

[gitignore](https://github.com/github/gitignore)


在最简单的情况下，一个仓库可能只根目录下有一个 .gitignore 文件，它递归地应用到整
个仓库中。 然而，子目录下也可以有额外的 .gitignore 文件。子目录中的 .gitignore
文件中的规则只作用于它所在的目录中。 （Linux 内核的源码库拥有 206 个 .gitignore 文
件。）
多个 .gitignore 文件的具体细节超出了本书的范围，更多详情见 man gitignore


git diff
此命令比较的是工作目录中当前文件和暂存区域快照之间的差异。 也就是修改之后还没有暂存起来的变化内
容

git commit 加上 -a 选项
Git 就会自动把所有已经跟踪过的文件暂存
起来一并提交，从而跳过 git add 步骤


git rm --cached
git rm -f
git rm 命令后面可以列出文件或者目录的名字，也可以使用 glob 模式
\* = *


git log
--stat
--pretty
![Alt text](image-1.png)
![Alt text](image-2.png)

记住，在 Git 中任何 已提交 的东西几乎总是可以恢复的。 甚至那些被删除的分支中的提交或使用 --amend 选
项覆盖的提交也可以恢复 （阅读 数据恢复 了解数据恢复）。 然而，任何你未提交的东西丢失后很可能再也找不
到了。
52

git remote


git remote add <shortname> <url>



git fetch
git push
git remote show
git pull
git remote rename
git remote rm

git tag
Git 支持两种标签：轻量标签（lightweight）与附注标签（annotated）。
轻量标签很像一个不会改变的分支——它只是某个特定提交的引用。
而附注标签是存储在 Git 数据库中的一个完整对象， 它们是可以被校验的，其中包含打标签者的名字、电子邮件
地址、日期时间， 此外还有一个标签信息，并且可以使用 GNU Privacy Guard （GPG）签名并验证。 通常会建
议创建附注标签，这样你可以拥有以上所有信息。但是如果你只是想用一个临时的标签， 或者因为某些原因不
想要保存这些信息，那么也可以用轻量标签


Git 别名 star





git 分支
这与过去大多数版本控制系统形成了鲜明的对比，它们在创建分支时，将所有的项目文件都复制一遍，并保存到
一个特定的目录。 完成这样繁琐的过程通常需要好几秒钟，有时甚至需要好几分钟。所需时间的长短，完全取
决于项目的规模。 而在 Git 中，任何规模的项目都能在瞬间创建新分支。 同时，由于每次提交都会记录父对
象，所以寻找恰当的合并基础（译注：即共同祖先）也是同样的简单和高效。 这些高效的特性使得 Git 鼓励开发
人员频繁地创建和使用分支。


git branch -d

git merge冲突


vscode 签出已分离

git branch -v
git branch -a

git branch --merged

git branch -d / -D

尽可能多创建分支，分支带来的开销非常小

许多使用 Git 的开发者都喜欢使用这种方式来工作，比如只在 master 分支上保留完全稳定的代码——有可能仅
仅是已经发布或即将发布的代码。 他们还有一些名为 develop 或者 next 的平行分支，被用来做后续开发或者
测试稳定性——这些分支不必保持绝对稳定，但是一旦达到稳定状态，它们就可以被合并入 master 分支了。 这
样，在确保这些已完成的主题分支（短期分支，比如之前的 iss53 分支）能够通过所有测试，并且不会引入更
多 bug 之后，就可以合并入主干分支中，等待下一次的发布。

![Alt text](image-3.png)




从一个远程跟踪分支检出一个本地分支会自动创建所谓的“跟踪分支”（它跟踪的分支叫做“上游分支”）。
跟踪分支是与远程分支有直接关系的本地分支。 如果在一个跟踪分支上输入 git pull，Git 能自动地识别去哪个服务器上抓取、合并到哪个分支

git checkout -b <branch> <remote>/<branch>

--track

git branch -u origin/serverfix

当设置好跟踪分支后，可以通过简写 @{upstream} 或 @{u} 来引用它的上游分支。 所以在
master 分支时并且它正在跟踪 origin/master 时，如果愿意的话可以使用 git merge @
{u} 来取代 git merge origin/master

git branch -vv 如果想要查看设置的所有跟踪分支

可以运行带有 --delete 选项的 git push 命令
来删除一个远程分支


使用merge快速合并
fast-forward


git rebase --onto

git rebase <basebranch> <topicbranch>


git rebase teamone/master





## github加速



.git

![Alt text](image-4.png)


流程通常如下：
1. 派生一个项目
2. 从 master 分支创建一个新分支
3. 提交一些修改来改进项目
4. 将这个分支推送到 GitHub 上
5. 创建一个拉取请求
6. 讨论，根据实际情况继续修改
7. 项目的拥有者合并或关闭你的拉取请求
8. 将更新后的 master 分支同步到你的派生中


