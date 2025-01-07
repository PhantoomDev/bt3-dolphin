// BT3 rollback: Load into prepare combat loading

#include "Core/CustomStateLoader.h"

#include "Common/Logging/Log.h"
#include "Core/Config/MainSettings.h"
#include "Core/Core.h"
#include "Core/PowerPC/MMU.h"
#include "Core/State.h"
#include "Core/System.h"
#include <Common/FileUtil.h>
#include "HW/ProcessorInterface.h"
#include "Core/State.h"

CustomStateLoader::CustomStateLoader(Core::System& system) : m_system(system)
{

}

CustomStateLoader::~CustomStateLoader() = default;

void CustomStateLoader::LoadPrepareCombat(std::array<u32, 14>& char_arr, u32& map_id)
{
  // Load prepared save state
  State::LoadAs(m_system, m_base_state_path);
  Core::CPUThreadGuard guard(m_system);

  // Character number logic, any character val over the number of character will be set to
  // 0xffffffff and color as 0x00000000
  for (unsigned int i = 1; i <= 3; i++)
  {
    int baseIdx = (i - 1) * 2 + 1;
    if (i > char_arr[0])
    {
      char_arr[baseIdx] = 0xffffffff;
      char_arr[baseIdx + 1] = 0x00000000;
    }
  }
  // Player 2
  for (unsigned int i = 1; i <= 3; i++)
  {
    int baseIdx = (i - 1) * 2 + 8;
    if (i > char_arr[7])
    {
      char_arr[baseIdx] = 0xffffffff;
      char_arr[baseIdx + 1] = 0x00000000;
    }
  }

  // Player 1 Character number
  PowerPC::MMU::HostWrite_U32(guard, char_arr[0], 0x912C634C);
  // Player 1 Characters and colors
  PowerPC::MMU::HostWrite_U32(guard, char_arr[1], 0x912C6234);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[2], 0x912C6230);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[3], 0x912C6264);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[4], 0x912C6260);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[5], 0x912C6294);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[6], 0x912C6290);
  // Player 2 Character number
  PowerPC::MMU::HostWrite_U32(guard, char_arr[7], 0x912C65D4);
  // Player 2 Characters and colors
  PowerPC::MMU::HostWrite_U32(guard, char_arr[8], 0x912C64BC);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[9], 0x912C64B8);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[10], 0x912C64EC);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[11], 0x912C64E8);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[12], 0x912C651C);
  PowerPC::MMU::HostWrite_U32(guard, char_arr[13], 0x912C6518);

  // Map input map
  PowerPC::MMU::HostWrite_U32(guard, map_id, 0x912C67CC);
}
