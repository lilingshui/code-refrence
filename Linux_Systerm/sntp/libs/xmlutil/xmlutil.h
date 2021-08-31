/*
 * xmlutil
 *
 * (C) Copyright 2016, Wasion Group
 * YuWeifeng, <yuweifeng@wasion.com>
 *
 */

#ifndef __XMLUTIL_H
#define __XMLUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

int add_xml_node(const char *parent, const char *name, const char *value);
int add_xml_node_attr(const char *node, const char *attr_name, const char *value);
int del_xml_node(const char *key);
int del_xml_node_attr(const char *node, const char *attr_name);
int set_xml_node_value(const char *key, const char *value);
int set_xml_node_attr(const char *key, const char *attr_name, const char *value);
int get_xml_node_value(const char *key, char *value);
int get_xml_node_attr_value(const char *node, const char *attr_name, char *value);

int open_xml_file(char *fname);
void close_xml_file(void);

#ifdef __cplusplus
}
#endif

#endif	/* __XMLUTIL_H */
