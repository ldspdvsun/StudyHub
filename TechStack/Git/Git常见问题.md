# VsCode中的git无法登录

> git push -u origin main
remote: Support for password authentication was removed on August 13, 2021.
remote: Please see https://docs.github.com/en/get-started/getting-started-with-git/about-remote-repositories#cloning-with-https-urls for information on currently recommended modes of authentication.
fatal: Authentication failed for 'https://github.com/ldspdvsun/StudyHub.git/'

这个问题是由于 GitHub 在2021年8月13日移除了对密码身份验证的支持所导致的。解决这个问题的方法是使用基于令牌（Token）的身份验证。

以下是解决该问题的步骤：

1. 打开 GitHub 的网站并登录到您的帐户。
2. 点击右上角的头像，选择 "Settings"（设置）。
3. 在左侧菜单中，选择 "Developer settings"（开发者设置）。
4. 在左侧菜单中，选择 "Personal access tokens"（个人访问令牌）。
5. 点击 "Generate new token"（生成新令牌）。
6. 提供一个描述以标识该令牌的用途，并选择适当的权限（scope）。至少需要勾选 "repo" 权限以便进行推送操作。
7. 点击 "Generate token"（生成令牌）。
8. 将生成的令牌复制到剪贴板中。

现在您可以在 VSCode 中使用令牌来进行身份验证：

1. 打开 VSCode 并导航到您的项目。
2. 打开终端（Terminal）。
3. 运行以下命令，将您的 GitHub 用户名和令牌替换为实际值：

```plaintext
git config --global credential.helper store
git config --global user.name "YourGitHubUsername"
git config --global user.email "your-email@example.com"
```

这些命令将配置 Git 以使用存储凭据并设置您的用户名和电子邮件地址。

4. 在终端中运行以下命令，将您的仓库 URL 中的用户名部分替换为您的 GitHub 用户名，并使用生成的令牌作为密码：

```plaintext
git remote set-url origin https://YourGitHubUsername:YourToken@github.com/ldspdvsun/StudyHub.git
```

确保将 "YourGitHubUsername" 替换为您的 GitHub 用户名，并将 "YourToken" 替换为您刚刚生成的令牌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。

5. 最后，再次运行 `git push -u origin main` 命令，现在应该能够成功进行推送。

通过这些步骤，您应该能够成功解决在 VSCode 中使用 Git 推送时的身份验证问题。