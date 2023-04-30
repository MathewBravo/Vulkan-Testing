#pragma once

// Locations of Queue Families 
struct QueueFamilyIndices {
	int graphicsFamily = -1;

	// Check that Queue Families locations were found
	bool isValid() {
		return graphicsFamily >= 0;
	}
};
