/*
 * xmlutil example
 *
 * (C) Copyright 2016, Wasion Group
 * YuWeifeng, <yuweifeng@wasion.com>
 *
 * CC-cmd:
 *   CROSS_COMPILE=arm-linux- prefix=$(TOPDIR)/output/usr DESTDIR=$(TOPDIR)/bin make demo
 *
 */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <xmlutil.h>

int main(int argc, char **argv)
{
	char buf[256] = { 0 };

	open_xml_file(NULL);

	if ((argc == 1) || !strcmp(argv[1], "init")) {
		add_xml_node("//HADT", "gpio", NULL);
		add_xml_node("//HADT/gpio", "PA0", NULL);
		add_xml_node_attr("//HADT/gpio/PA0", "role", "io");
		add_xml_node_attr("//HADT/gpio/PA0", "direction", "output");
		add_xml_node_attr("//HADT/gpio/PA0", "init_level", "0");
		add_xml_node_attr("//HADT/gpio/PA0", "active_level", "1");
		add_xml_node("//HADT/gpio", "PA1", NULL);
		add_xml_node_attr("//HADT/gpio/PA1", "role", "io");
		add_xml_node_attr("//HADT/gpio/PA1", "direction", "output");
		add_xml_node_attr("//HADT/gpio/PA1", "init_level", "0");
		add_xml_node_attr("//HADT/gpio/PA1", "active_level", "1");
	} else if (!strcmp(argv[1], "add")) {
		add_xml_node("//HADT/gpio", "PA2", NULL);
		add_xml_node_attr("//HADT/gpio/PA2", "role", "io");
		add_xml_node_attr("//HADT/gpio/PA2", "direction", "output");
		add_xml_node_attr("//HADT/gpio/PA2", "init_level", "0");
		add_xml_node_attr("//HADT/gpio/PA2", "active_level", "1");
	} else if  (!strcmp(argv[1], "del")) {
		del_xml_node("//HADT/gpio/PA1");
		del_xml_node_attr("//HADT/gpio/PA2", "direction");
	} else if (!strcmp(argv[1], "set")) {
		set_xml_node_attr("//HADT/gpio/PA0", "role", "Peripheral A");
	} else if (!strcmp(argv[1], "get")) {
		get_xml_node_attr_value("//HADT/gpio/PA0",  "role", buf);
		printf("get PA0 role: %s\n", buf);
	}


	close_xml_file();
	return 0;
}
