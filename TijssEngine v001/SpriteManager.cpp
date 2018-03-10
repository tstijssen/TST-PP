#include "SpriteSheet.h"

using namespace smanager;

int SpriteManager::AddSprite(SpriteSheet* newSprite)
{
	m_AllSprites.push_back(newSprite);
	return m_AllSprites.size() - 1;
}

void SpriteManager::RemoveSprite(int index)
{
	m_AllSprites.erase(m_AllSprites.begin() + index);
}

bool SpriteManager::DetectCollisions(int index)
{
	int aX;
	int aY;
	int aWidth;
	int aHeight;
	int aRadius;

	std::vector<SpriteSheet*>::iterator targetSprite = m_AllSprites.begin() + index;

	switch ((*targetSprite)->collision)
	{
	case CollisionType::Box:
	{
		aWidth = (*targetSprite)->size.x;		 // maxX
		aHeight = (*targetSprite)->size.y;		 // maxY
		aX = (*targetSprite)->position.x - aWidth / 2;	 // minX
		aY = (*targetSprite)->position.y - aWidth / 2;	 // minY
		break;
	}
	case CollisionType::Circle:
	{
		aX = (*targetSprite)->position.x;
		aY = (*targetSprite)->position.y; 
		aRadius = (*targetSprite)->radius;
		break;
	}
	case CollisionType::Point:
	{
		aX = (*targetSprite)->position.x;
		aY = (*targetSprite)->position.y;		
		break;
	}
	default:
		break;
	}

	for (std::vector<SpriteSheet*>::iterator it = m_AllSprites.begin(); it != m_AllSprites.end(); ++it)
	{
		if ((*it)->collision != CollisionType::None && it != targetSprite)
		{
			int bX;
			int bY;
			int bWidth;
			int bHeight;
			int bRadius;
			switch ((*it)->collision)
			{
			case CollisionType::Box:
			{
				bWidth = (*it)->size.x;				// maxX
				bHeight = (*it)->size.y;			// maxY
				bX = (*it)->position.x - bWidth / 2;				// minX
				bY = (*it)->position.y - bWidth / 2;				// minY

				switch ((*targetSprite)->collision)
				{
					// static = box, moving = box
				case CollisionType::Box:
				{
					if ((abs(aX - bX) * 2 < (aWidth + bWidth)) &&
						(abs(aY - bY) * 2 < (aHeight + bHeight)))
					{
						return true;
					}
					break;
				}
				// static = box, moving = circle
				case CollisionType::Circle:
				{
					auto halfWidth = bWidth / 2;
					auto halfHeight = bHeight / 2;

					auto distX = abs(aX - bX - halfWidth);
					auto distY = abs(aY - bY - halfHeight);

					if (distX > (halfWidth + aRadius)) { return false; };
					if (distY > (halfHeight + aRadius)) { return false; };

					if (distX <= (halfWidth)) { return true; };
					if (distY <= (halfHeight)) { return true; };

					auto pX = distX - halfWidth;
					auto pY = distY - halfHeight;

					return(pX * pX + pY * pY <= (aRadius * aRadius));

					//bX -= aRadius;
					//bWidth += aRadius;
					//bY -= aRadius;
					//bHeight += aRadius;
					//if (aX > bX && aX < bWidth && aY > bY && aY < bHeight)
					//{
					//	return true;
					//}
					break;
				}
				// static = box, moving = point
				case CollisionType::Point:
				{
					if (aX > bX && aX < bWidth && aY > bY && aY < bHeight)
					{
						return true;
					}
					break;
				}
				default:
					break;
				}
				break;
			}			
			case CollisionType::Circle:
			{
				bX = (*it)->position.x;
				bY = (*it)->position.y;
				bRadius = (*it)->radius;

				switch ((*targetSprite)->collision)
				{
					// static = circle, moving = box
				case CollisionType::Box:
				{
					auto halfWidth = aWidth / 2;
					auto halfHeight = aHeight / 2;

					auto distX = abs(bX - aX - halfWidth);
					auto distY = abs(bY - aY - halfHeight);

					if (distX > (halfWidth + bRadius)) { return false; };
					if (distY > (halfHeight + bRadius)) { return false; };

					if (distX <= (halfWidth)) { return true; };
					if (distY <= (halfHeight)) { return true; };

					auto pX = distX - halfWidth;
					auto pY = distY - halfHeight;

					return(pX * pX + pY * pY <= (bRadius * bRadius));
					break;
				}
				// static = circle, moving = circle
				case CollisionType::Circle:
				{
					int x = abs(aX - bX);
					int y = abs(aY - bY);
					int distance = sqrt(x * x + y * y);

					if (distance < aRadius + bRadius)
					{
						return true;
					}
					break;
				}
				// static = circle, moving = point
				case CollisionType::Point:
				{
					int x = abs(bX - aX);
					int y = abs(bY - aY);
					int distance = sqrt(x * x + y * y);

					if (distance < bRadius)
					{
						return true;
					}
					break;
				}
				default:
					break;
				}
				break;
			}			
			case CollisionType::Point:
			{
				bX = (*it)->position.x;
				bY = (*it)->position.y;

				switch ((*targetSprite)->collision)
				{
					// static = point, moving = box
				case CollisionType::Box:
				{
					if (bX > aX && bX < aWidth && bY > aY && bY < aHeight)
					{
						return true;
					}
					break;
				}
				// static = point, moving = circle
				case CollisionType::Circle:
				{
					int x = abs(aX + bX);
					int y = abs(aY + bY);
					int distance = sqrt(x * x + y * y);

					if (distance < aRadius)
					{
						return true;
					}
					break;
				}
				// static = point, moving = point
				case CollisionType::Point:
				{
					if (aX == bX && aY == bY)
					{
						return true;
					}
					break;
				}
				default:
					break;
				}
				break;
			}	
			default:
				break;
			}
		}
	}
	return false;
}