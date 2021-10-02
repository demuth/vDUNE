#include "vDuneCore/Public/Avatar/Interfaces/Tools/AvatarTool.h"


UAvatarTool::UAvatarTool()
{
    mode_type_ = EAvatarMode::Tool;
    tool_type_ = EAvatarTool::None;
}

EAvatarTool UAvatarTool::get_tool_type()
{
    return tool_type_;
}