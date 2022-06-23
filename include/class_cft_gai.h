/* 邹良顺 2152611 信02 */
#pragma once

#include "../include/class_cft.h"

#if ENABLE_LIB_TCFG_TOOLS

#include "../include/lib_tcfg_tools_get_all_item.h"
typedef tcft_gai	cft_gai;		//将tcft_gai声明为cft_gai

#else

/* 目前照抄lib_tcfg_tools_get_all_items.h，允许按规定要求做变化 */
/* gai = get_all_item ：get_all_item_from_one_group */
class cft_gai : public  cft {
protected:
	char pad[256];

public:
	int item_add(const char* group_name, const char* item_value);	//跟ctf不同，NULL
	int item_add(const char* group_name, const string& item_value);	//跟ctf不同，NULL

	int item_update() const; //通过这种方法禁止使用ctf类的所有update函数（强制加ctf::不在限制范围内）

	int item_del(const char* group_name, const char* item_value);
	int item_del(const char* group_name, const string& item_value);

	string* item_get_all(const char* group_name);
};

#endif
