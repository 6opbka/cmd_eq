# cmd_eq

Terminal audio player in C++ with ncurses UI.

## Features
- Audio playback (miniaudio)
- FPS counter
- Keyboard control
- Lock-free audio ↔ UI communication

## Architecture
- Renderer — input + rendering
- AudioPlayer — audio thread
- Coordinator — main loop
- Shared atomic state + command channel

## Build
```bash
mkdir build 
cd build
cmake -G ninja .
ninja
```
## TODO
- [x] Audio class
- [x] Renderer class
- [x] UI class  
- [x] Data bus between above
- [ ] Data bus for controls
- [ ] Metadata parsing
- [ ] Somewhat UI
- [ ] Audio visualisation
- [ ] Config file
- [ ] Reading playlist from dir  







