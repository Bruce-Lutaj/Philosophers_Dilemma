#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_room	room;

	philo = NULL;
	room = (t_room){0};
	if (!parse_args(ac, av))
		return (0);
	if (!init(&room, ac, av))
		return (0);
	room_routine(&room);
	free_all(&room);
	return (0);
}
