// BT3 rollback: Load into prepare combat loading

#pragma once

#include <string>
#include <vector>

#include "Common/CommonTypes.h"
#include "Core/System.h"
#include "Common/FileUtil.h"

namespace Core
{
class System;
class CPUThreadGuard;
}  // namespace Core

class CustomStateLoader
{
public:
  // Structure to hold memory modifications we want to make
  struct MemoryPatch
  {
    u32 address;
    u32 value;
  };

  explicit CustomStateLoader(Core::System& system);
  ~CustomStateLoader();

  // Prevent copying to ensure proper resource management
  CustomStateLoader(const CustomStateLoader&) = delete;
  CustomStateLoader& operator=(const CustomStateLoader&) = delete;

  // Public interface
  void LoadPrepareCombat();
  void SetSelectionValues(std::array<u32, 14>& char_arr, u32& map_id);

private:

  Core::System& m_system;
  std::string m_base_state_path = File::GetSysDirectory()+"CustomStates/RDSPAF_base.sav";
  std::vector<MemoryPatch> m_patches;
};
