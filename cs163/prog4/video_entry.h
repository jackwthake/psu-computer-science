/*
 * Jack Thake, CS163, Karla Fant
 * This file holds the definition for the video_entry class.
*/

#ifndef VIDEO_ENTRY_H
#define VIDEO_ENTRY_H

/* one video */
class video_entry {
  public:
    video_entry(); /* constructor */
    video_entry(char *class_name, char *media_name, char *desc, int len, char *next); /* constructor */
    ~video_entry(); /* deconstructor */

    int print(void) const; /* print self */
    bool is_valid(void) const; /* check if we're a valid object */
    bool is_same_course(const char *b) const; /* check if we're in the same course */
    
    /* overloaded operators */
    void operator=(const video_entry &);
    bool operator==(const video_entry &) const;
    bool operator==(const char *) const;
    bool operator<(const video_entry &) const;
    bool operator<(const char *) const;
  private:
    char *class_name, *media_name, *desc, *next; 
    int len;
};

#endif
