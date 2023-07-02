# 安装

```sh
sudo apt update
sudo apt install zsh
sudo apt install wget git
sh -c "$(wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh -O -)"
chsh -s $(which zsh)

```

# 插件

## 命令自动提示
```sh
wget http://mimosa-pudica.net/src/incr-0.2.zsh
mkdir ~/.oh-my-zsh/plugins/incr
mv incr-0.2.zsh ~/.oh-my-zsh/plugins/incr
echo 'source ~/.oh-my-zsh/plugins/incr/incr*.zsh' >> ~/.zshrc
source ~/.zshrc
```

## autojump

```sh
sudo apt install autojump
```

将 autojump 添加到插件列表中，例如：
```sh
vim ~/.zshrc

plugins=(
  git
  autojump
)

source ~/.zshrc
```



## 
```sh
git clone https://github.com/zsh-users/zsh-autosuggestions.git $ZSH_CUSTOM/plugins/zsh-autosuggestions
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git $ZSH_CUSTOM/plugins/zsh-syntax-highlighting

```

# 参考链接

> https://zhuanlan.zhihu.com/p/62501175