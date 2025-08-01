#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
	Command() = default;
	Command(const Command& rhs) = delete;
	Command& operator=(const Command& rhs) = delete;
	virtual ~Command() = default;

	virtual void Execute() = 0;
};

#endif