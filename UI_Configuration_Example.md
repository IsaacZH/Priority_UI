## 
[UI_LINE] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = LINE, // UI内容类型
.ui_config.name = "g1", // 图形名称
/可变配置**/
.ui_config.operate_type = MODIFY, // 操作类型
.ui_config.layer = 1, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 100, // 起点 x 坐标
.ui_config.start_y = 100, // 起点 y 坐标
.ui_config.end_x = 200, // 终点 x 坐标
.ui_config.end_y = 200, // 终点 y 坐标
},
[UI_CIRCLE] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = CIRCLE, // UI内容类型
.ui_config.name = "g2", // 图形名称
/可变配置**/
.ui_config.operate_type = MODIFY, // 操作类型
.ui_config.layer = 1, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 200, // 圆心 x 坐标
.ui_config.start_y = 200, // 圆心 y 坐标
.ui_config.radius = 40, // 半径
},
[UI_RECTANGEL] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = RECTANGEL, // UI内容类型
.ui_config.name = "g3", // 图形名称
/可变配置**/
.ui_config.operate_type = MODIFY, // 操作类型
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 0, // 左上角 x 坐标
.ui_config.start_y = 0, // 左上角 y 坐标
.ui_config.end_x = 0, // 右下角 x 坐标
.ui_config.end_y = 0, // 右下角 y 坐标
},
[UI_ELLIPSE] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = ELLIPSE, // UI内容类型
.ui_config.name = "g4", // 图形名称
/可变配置**/
.ui_config.operate_type = MODIFY, // 操作类型
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 0, // 圆心 x 坐标
.ui_config.start_y = 0, // 圆心 y 坐标
.ui_config.end_x = 0, // x 半轴长度
.ui_config.end_y = 0, // y 半轴长度
},
[UI_ARC] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = ARC, // UI内容类型
.ui_config.name = "g5", // 图形名称
/可变配置**/
.ui_config.operate_type = MODIFY, // 操作类型
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 0, // 圆心 x 坐标
.ui_config.start_y = 0, // 圆心 y 坐标
.ui_config.end_x = 0, // x 半轴长度
.ui_config.end_y = 0, // y 半轴长度
.ui_config.start_angel = 0, // 起始角度
.ui_config.end_angel = 0, // 终止角度
},
[UI_FLOAT] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = FLOAT, // UI内容类型
.ui_config.name = "g6", // 图形名称
/可变配置**/
.ui_config.operate_type = MODIFY, // 操作类型
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.size = 20, // 字体大小
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 0, // 起点 x 坐标
.ui_config.start_y = 0, // 起点 y 坐标
.ui_config.float_num = 0, // 显示的数字
.ui_config.decimal = 0, // 小数位有效个数
},
[UI_INT] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = INT, // UI内容类型
.ui_config.name = "g7", // 图形名称
/可变配置**/
.ui_config.operate_type = MODIFY, // 操作类型
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.size = 20, // 字体大小
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 0, // 起点 x 坐标
.ui_config.start_y = 0, // 起点 y 坐标
.ui_config.int_num = 0, // 显示的数字
},
[UI_CHAR] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = CHAR, // UI内容类型
.ui_config.name = "g8", // 图形名称
/可变配置**/
.ui_config.operate_type = MODIFY, // 操作类型
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.size = 20, // 字体大小
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 200, // 起点 x 坐标
.ui_config.start_y = 200, // 起点 y 坐标
.ui_config.text = "Fuck", // 显示的文字
},
};

ui_info_t const_ui_info [] =
{
[UI_LINE] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = LINE, // UI内容类型
.ui_config.name = "g9", // 图形名称
/可变配置**/
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 0, // 起点 x 坐标
.ui_config.start_y = 0, // 起点 y 坐标
.ui_config.end_x = 0, // 终点 x 坐标
.ui_config.end_y = 0, // 终点 y 坐标
},
[UI_CIRCLE] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = CIRCLE, // UI内容类型
.ui_config.name = "g10", // 图形名称
/可变配置**/
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 10, // 圆心 x 坐标
.ui_config.start_y = 50, // 圆心 y 坐标
.ui_config.radius = 200, // 半径
},
[UI_RECTANGEL] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = RECTANGEL, // UI内容类型
.ui_config.name = "g11", // 图形名称
/可变配置**/
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 0, // 左上角 x 坐标
.ui_config.start_y = 100, // 左上角 y 坐标
.ui_config.end_x = 100, // 右下角 x 坐标
.ui_config.end_y = 0, // 右下角 y 坐标
},
[UI_ELLIPSE] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = ELLIPSE, // UI内容类型
.ui_config.name = "g12", // 图形名称
/可变配置**/
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 800, // 圆心 x 坐标
.ui_config.start_y = 800, // 圆心 y 坐标
.ui_config.end_x = 10, // x 半轴长度
.ui_config.end_y = 80, // y 半轴长度
},
[UI_ARC] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = ARC, // UI内容类型
.ui_config.name = "g13", // 图形名称
/可变配置**/
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 89, // 圆心 x 坐标
.ui_config.start_y = 40, // 圆心 y 坐标
.ui_config.end_x = 20, // x 半轴长度
.ui_config.end_y = 40, // y 半轴长度
.ui_config.start_angel = 0, // 起始角度
.ui_config.end_angel = 40, // 终止角度
},
[UI_FLOAT] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = FLOAT, // UI内容类型
.ui_config.name = "g14", // 图形名称
/可变配置**/
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.size = 20, // 字体大小
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = 190, // 起点 x 坐标
.ui_config.start_y = 46, // 起点 y 坐标
.ui_config.float_num = 3.65, // 显示的数字
.ui_config.decimal = 2, // 小数位有效个数
},
[UI_INT] = {
/不变配置**/
.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = INT, // UI内容类型
.ui_config.name = "g15", // 图形名称
/可变配置**/
.ui_config.layer = 0, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.size = 20, // 字体大小
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = Client_mid_position_x, // 起点 x 坐标
.ui_config.start_y = Client_mid_position_y, // 起点 y 坐标
.ui_config.int_num = 666, // 显示的数字
},
[UI_CHAR] = {
/不变配置**/

.ui_config.priority = PRIORITY_HIGH, // UI优先级(仅动态UI需要配置)
.ui_config.ui_type = CHAR, // UI内容类型
.ui_config.name = "g16", // 图形名称
/可变配置**/
.ui_config.layer = 2, // 图层数，0~9
.ui_config.color = GREEN, // 颜色
.ui_config.size = 20, // 字体大小
.ui_config.width = 2, // 线条宽度
.ui_config.start_x = Client_mid_position_x + 200, // 起点 x 坐标
.ui_config.start_y = Client_mid_position_y + 84, // 起点 y 坐标
.ui_config.text = "LOL", // 显示的文字
},
