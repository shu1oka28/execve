execve
================

execveシステムコールを用いたコマンドを呼び出すプログラム

インストール方法
----------------
Ubuntuを想定
```bash
sudo apt install git gcc
git clone https://github.com/shu1oka28/execve.git
gcc -Wall -Wextra run.c
```

使い方
-------------

```bash
$ ./a.out
commnand> /usr/bin/git add -A
commnand> /usr/bin/git status
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	modified:   README.md
	modified:   run.c

$ ./a.out
commnand> /usr/bin/date
Fri Sep 17 20:34:20 JST 2021
commnand> /usr/bin/git status
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	modified:   README.md
	modified:   run.c

commnand> ./a.out
commnand> cat         
catコマンドが実行できませんでした
error in execve: : No such file or directory
commnand> (^D)commnand> (^D)
```
`(^D)`はCtrl+Dを押したことを示しており、実際は表示されません。