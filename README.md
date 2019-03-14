# build-button
A bluetooth build button project

## button-launcher

Symlink button-launcher into your PATH:
`sudo ln -s <this repo dir>/button-launcher/button-launcher /usr/local/bin/button-launcher`

Add to your `~/.bash_profile`:
`bind -x '"\C-^":"button-launcher"'`

Add to your vim config for vim-test:
`nmap <silent> <C-^> :TestNearest<CR>`
