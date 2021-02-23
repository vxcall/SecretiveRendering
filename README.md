![cpp](https://img.shields.io/badge/C%2B%2B-17-%23ff40d9.svg?style=flat)
![cmake](https://img.shields.io/badge/cmake-3.16-yellow)
![License](http://img.shields.io/badge/license-MIT-yellowgreen.svg?style=flat)

![header](https://user-images.githubusercontent.com/33578715/108846417-7ee30800-7619-11eb-9022-a98085ccfbea.png)

# :neckbeard: Steam-overlay-abusion

**Please :star:star this project, it'll be a huge help for me =)**

Recently, I've gotten a vivid inspiration when I first take a look at **[gameoverlayrenderer-imgui-dx9](https://github.com/aixxe/gameoverlayrenderer-imgui-dx9)**, 
so I decided to replicate this repository in alternative and simpler way which uses Minhook within the hooking process. In addition, the original repository made 4 years prior from now,
and some of the syntax and libraries it uses are no longer valid, that's also the reason I made this.

Basically, this technology abuses overlay feature in Steam and it allows you to render anything in completely invisible state on your stream.
This way you can stream any hacky stuff without letting viewers know that you're cheating.


# How it looks

**LEFT**: OBS window | **RIGHT**: actual game window

You don't see hack menu at all on OBS, do you?
![image](https://user-images.githubusercontent.com/33578715/108908093-e15df780-765d-11eb-9bc4-268f21f55290.png)

# TODO
- [x] Render hack menu with imgui