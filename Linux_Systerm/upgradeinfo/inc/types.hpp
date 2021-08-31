#ifndef _TYPES_HPP
#define _TYPES_HPP

#define UCHAR unsigned char

struct Point {
  int x;
  int y;
};

struct Position {
  int col;
  int row;
};

/* enum KEYS {*/
/*   UPWARD	= 2, */
/*   DOWNWARD	= 3,*/
/*   LEFTWARD	= 4,*/
/*   RIGHTWARD	= 5, */
/*   CANCEL	= 0, */
/*   ENTER		= 1*/
/* };*/



enum COLLECTION_MODE {
  BYTURN = 0, FREEZE = 1, PROFILE = 2
};

/* struct MeterArchive {*/
/*   char line_no[4];*/
/*   enum PROTOCOLS protocol;*/
/*   char addr[12];*/
/*   enum COLLECTION_PLAN  plan;*/
/*   enum BAUDRATE baudrate;*/
/*   enum COLLECTION_MODE mode;*/
/* };*/



#endif /*_TYPES_HPP*/
