#include "string.h"
#include "queue.h"

ERROR_CODE queue_init(queueP_t queue, uint16_t size, uint32_t depth)
{
	int8_t *data = (int8_t *)malloc(depth * size * sizeof(int8_t));

	return queue_init2(queue, size, depth, data);
}

ERROR_CODE queue_init2(queueP_t queue, uint16_t size, uint32_t depth, int8_t *data)
{
	ERROR_CODE error = STATUS_NORMAL;

	if(queue == NULL)
	{
		error = ERR_POINTER_0;
	}
	else if(data == NULL)
	{
		error = ERR_POINTER_0;
	}
	else if(depth == 0UL)
	{
		error = ERR_PARAMETER;
	}
	else if(size == 0UL)
	{
		error = ERR_PARAMETER;		
	}
	else
	{
		queue->front = 0UL;
		queue->rear = queue->front;
		queue->depth = depth;
		queue->size = size;
		queue->event = data;
		memset(queue->event, 0, depth * size * sizeof(char));
	}

	return error;
}

int queue_push(queueP_t queue, void *src)
{
	int8_t *p = queue->event;
	int8_t *event, *s = src;
	uint8_t index = queue->size;

	if(queue_full(queue))
	{
		return ERR_FULL;
	}
	(queue->rear) %= queue->depth;			/* 到队列底返回到队头 */
	event = &p[(queue->rear++) * queue->size];
	while(index--)
	{
		*event++ = *s++;
	}
	return STATUS_NORMAL;
}

int queue_pop(queueP_t queue, void *dest)
{
	int8_t *p = queue->event;
	int8_t *event, *d = dest;
	uint8_t index = queue->size;
	
	if(queue_empty(queue))
	{
		return ERR_EMPTY;
	}						    
	queue->front %= queue->depth;		/* 到队列底返回到队头 */
	event = &p[(queue->front++) * queue->size];
	while(index--)
	{
		*d++ = *event++;
	}
	return STATUS_NORMAL;
}

