
//Navigation by Harriet Moore
void Player::update()
{
	if (currentCell->hasDoor())
	{
		currentCell->OpenDoor();
	}
}