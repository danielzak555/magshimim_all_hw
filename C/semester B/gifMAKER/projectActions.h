#ifndef PROJECTACTIONS_H
#define PROJECTACTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"
#include "view.h"

FrameNode* gifLoad(FrameNode* head, char* path);
void gifSave(FrameNode* head, char* path);

#endif