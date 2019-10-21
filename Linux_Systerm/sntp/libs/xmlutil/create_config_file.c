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
#include "xmlutil.h"

int main(int argc, char **argv)
{
	char buf[256] = { 0 };

	open_xml_file("setting.xml");
	
	add_xml_node("//wasion", "server", NULL);
	add_xml_node_attr("//wasion/server", "address", "192.168.221.250");

	add_xml_node("//wasion", "timezone", NULL);
	add_xml_node_attr("//wasion/timezone", "value", "8");

	close_xml_file();
	return 0;
}
