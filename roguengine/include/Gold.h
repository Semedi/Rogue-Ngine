#ifndef GOLD_H
#define GOLD_H

#include <Item.h>

class Gold : public Item
{
public:
	/**
	 * Default constructor.
	 */
	Gold();

	/**
	 * Gets the amount of gold this pickup has.
	 * @return The amount of gold the pickup has.
	 */
	int GetGoldValue() const;

private:
	/**
	 * The value of this gold pickup.
	 */
	int goldValue;
};
#endif