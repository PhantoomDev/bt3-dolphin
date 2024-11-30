# Dragon Ball Z: Budokai Tenkaichi 3 Dolphin (Rollback Netcode Implementation)

## Overview
This is fork of Dolphin emulator specifically modified to support rollback netcode for Dragon Ball Z: Budokai Tenkaichi 3. This project works in conjunction with the [BT3 reverse engineering project](https://github.com/PhantoomDev/bt3-re) to provide a complete rollback netplay solution.

Refer to the **[Original readme](/original_readme.md)** for dolphin build, run and more.

## Features
- Rollback netcode implementation
- Virtual input device system
- Network synchronization
- State management and restoration
- Performance optimizations for BT3

## Technical Architecture

### Game Modifications*
*On the other repo**

- Utilizing unused "Dragon Net Battle" section as entry point for code injection
- Implementing custom interface for netplay battle
- Separating core components:
  - Game logic
  - Rendering pipeline
  - Audio callback system
- Creating hooks for Dolphin emulator interaction

### Dolphin Implementation
Based on Slippi architecture:
- Virtual input device system for netplay opponent
- Input buffer management
- State preservation system
- Rollback implementation:
  - Input difference detection
  - Game state rollback mechanism
  - Logic recalculation
  - Render update system

## Project Roadmap

### Phase 1: Dolphin Integration
- [ ] Virtual Input System
  - [ ] Implement Slippi-style input device
  - [ ] Create input buffer management
  - [ ] Develop network input handling
- [ ] Rollback System
  - [ ] Implement state saving/loading
  - [ ] Create prediction system
  - [ ] Develop frame rollback mechanism
- [ ] Network Implementation
  - [ ] Create peer-to-peer connection system
  - [ ] Implement input synchronization
  - [ ] Develop delay adjustment system

### Phase 2: Polish & Testing
- [ ] Alpha Testing
  - Conduct extensive edge-case testing
  - Gather player feedback
  - Document and address stability issues
- [ ] Performance Optimization
  - [ ] Optimize state saving
  - [ ] Improve rollback performance
  - [ ] Minimize network overhead

### Prototype rough outline
```
## Modded Dolphin Side:
1. Basic UI
   - Simple dropdown menus for characters/stage selection
   - Host/Join buttons

2. Session Flow
   Host: (p2p protocol)
   - Pick both chars + stage
   - Wait for player

   Join: (join with p2p code)
   - Auto run ping test -> calculate delay/rollback frames
   - Pick own char

3. When both ready:
   - Map selections to game's character/stage IDs
   - Send to game's duel mode function
   - Jump to combat prepare state

4. During Fight:
   Normal case:
   - Run game normally when predictions correct

   When desync/rollback needed:
   Ideal: 
   - Run only necessary game logic (requires combat game state to recalculate)
   - Recalculate with new predicted inputs
   - Render current frame
   - Resume

   Fast prototype fallback:
   - Brute force replay entire game state from wrong input to current frame
   - Resume

Done!
```

## Technical Considerations

### Virtual Input System
- Input buffer size: TBD
- Input delay handling
- Network packet format
- State synchronization protocol

### Performance Targets
- Frame delay: <2 frames (out of 30 fps)
- Rollback window: Up to 7 frames
- State save size: TBD
- Memory overhead: TBD

## Current Status
- Reverse engineering: In Progress
- Code injection research: Not Started
- Dolphin modification: Planning Phase
- Netplay implementation: Not Started


## Resources
- [GGPO Documentation](https://github.com/pond3r/ggpo)
- [Dolphin Development Guide](https://dolphin-emu.org/docs/guides/)
- [Slippi Project Reference](https://github.com/project-slippi)
