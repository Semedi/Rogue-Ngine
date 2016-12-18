#ifndef HEART_H
#define HEART_H

#include "Item.h"

class Heart : public Item
{
public:

	/**
	 * Default constructor.
	 */
	Heart();

	/**
	 * Returns the amount of health that the heart gives.
	 * @return The amount of health the heart gives.
	 */
	int GetHealth() const;

private:

	/**
	 * The amount of health the heart gives.
	 */
	int m_health;
};
#endif