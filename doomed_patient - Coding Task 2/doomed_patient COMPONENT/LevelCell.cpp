void LevelCell::OpenDoor()
{
	for (auto& element : edges)
	{
		std::shared_ptr<CellEdge> edge = element.second;
		if (edge->isDoor())
		{
			edge->sprite = game->getHorizontalDoorOpenSprite();
		}
	}
}
