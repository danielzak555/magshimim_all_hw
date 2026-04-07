#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE

// Frame struct
typedef struct Frame
{
	char*		name;
	unsigned int	duration;
	char*		path;  
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

int frameNameExists(FrameNode* head, char* name);

int getListLength(FrameNode* head);

FrameNode* addFrame(FrameNode* head, Frame* newFrame);

FrameNode* removeFrame(FrameNode* head, char* frameName);

FrameNode* changeFrameIndex(FrameNode* head, char* frameName, int newIndex);

int changeFrameDuration(FrameNode* head, char* frameName, int newDuration);

void changeAllFramesDuration(FrameNode* head, int newDuration);

void listFrames(FrameNode* head);

void playGif(FrameNode* head);

void freeFrames(FrameNode* head);

#endif