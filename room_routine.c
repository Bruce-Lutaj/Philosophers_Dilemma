#include "philo.h"

int	check_odd(t_room *pRoom, int i)
{
	if (i % 2)
	{
		if (pRoom->time > pRoom->time_to_die + 5)
			return (0);
	}
	else
	{
		if (pRoom->time > pRoom->time_to_die)
			return (0);
	}
	return (1);
}

int	check_task(t_room *pRoom)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&pRoom->philo[i].mutex_philo);
	if (pRoom->philo[i].eat_count == pRoom->must_eat)
	{
		pthread_mutex_unlock(&pRoom->philo[i].mutex_philo);
		pRoom->count++;
		if (pRoom->count == pRoom->philos_nbr)
			return (1);
	}
	else
		pthread_mutex_unlock(&pRoom->philo[i].mutex_philo);
	return (0);
}

int	check_philos(t_room *pRoom)
{
	int	i;
	int	time;

	i = 0;
	pRoom->count = 0;
	time = get_milliseconds();
	while (i < pRoom->philos_nbr)
	{
		pthread_mutex_lock(&pRoom->philo[i].mutex_philo);
		pRoom->time = (time - pRoom->start_time) - pRoom->philo[i].last_meal;
		pthread_mutex_unlock(&pRoom->philo[i].mutex_philo);
		if (!check_odd(pRoom, i))
		{
			pthread_mutex_lock(&pRoom->mutex_room);
			pRoom->death = 1;
			pthread_mutex_unlock(&pRoom->mutex_room);
			p_death(&pRoom->philo[i]);
			return (0);
		}
		if (pRoom->must_eat && check_task(pRoom))
			return (0);
		i++;
	}
	return (1);
}

void	room_routine(t_room *pRoom)
{
	int	i;
	int	must_eat;

	i = 0;
	must_eat = pRoom->must_eat;
	while (42)
	{
		if (!check_philos(pRoom))
			break ;
	}
	while (i < pRoom->philos_nbr)
	{
		pthread_join(pRoom->philo[i].id, NULL);
		i++;
	}
}
