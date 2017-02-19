#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <Command.h>
#include <queue>


class CommandQueue
{
public:

	void push(const Command& command)
	{
		_Queue.push(command);
	}

	Command	pop()
	{
		Command command = _Queue.front();
		_Queue.pop();
		return command;

	}
	bool isEmpty() const
	{
		return _Queue.empty();
	}


private:
	std::queue<Command> _Queue;
};

#endif // COMMANDQUEUE_H
