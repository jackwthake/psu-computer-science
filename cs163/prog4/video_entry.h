#ifndef VIDEO_ENTRY_H
#define VIDEO_ENTRY_H

#include <cstring>

class video_entry {
  public:
    video_entry();
    video_entry(char *class_name, char *media_name, char *desc, int len, char *next);
    ~video_entry();

    int print(void) const;
    bool is_valid(void) const;
    bool is_same_course(const char *b) const;
    
    void operator=(const video_entry &);
    bool operator==(const video_entry &) const;
    bool operator<(const video_entry &) const;
    bool operator<(const char *) const;
    bool operator==(const char *) const;
  private:
    char *class_name, *media_name, *desc, *next; 
    int len;
};

#endif
