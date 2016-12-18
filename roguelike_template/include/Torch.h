#ifndef TORCH_H
#define TORCH_H

#include "Item.h"

class Torch : public Object
{
public:

	/**
	 * Default Constructor.
	 */
	Torch();

	/**
	 * Updates the brightness of the torch.
	 * @param timeDelta The time that has passed since the last update.
	 */
	void Update(float timeDelta) override;

	/**
	 * Gets the brightness modifier of the torch. This is used to create flicker.
	 * @return The brightness of the torch.
	 */
	float GetBrightness();

private:

	/**
	 * The brightness modifier of the torch. This is used to denote flicker.
	 */
	float m_brightness;
};
#endif