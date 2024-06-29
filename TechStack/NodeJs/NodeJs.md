# fnm

## installs fnm (Fast Node Manager)
curl -fsSL https://fnm.vercel.app/install | bash

## download and install Node.js
fnm use --install-if-missing 20

## verifies the right Node.js version is in the environment
node -v # should print `v20.15.0`

## verifies the right NPM version is in the environment
npm -v # should print `10.7.0`

# nvm

## installs nvm (Node Version Manager)
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash

## download and install Node.js (you may need to restart the terminal)
nvm install 20

## verifies the right Node.js version is in the environment
node -v # should print `v20.15.0`

## verifies the right NPM version is in the environment
npm -v # should print `10.7.0`
# 链接
https://nodejs.org/en/download/package-managerhttps://nodejs.org/en/download/package-manager