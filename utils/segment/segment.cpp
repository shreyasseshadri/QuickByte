#include "./segment.hpp"

void link_segments(Segment *prevSegment, Segment *nextSegment)
{
    prevSegment->next = nextSegment;
    nextSegment->prev = prevSegment;
}