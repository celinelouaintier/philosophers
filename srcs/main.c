/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouaint <clouaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:41:10 by clouaint          #+#    #+#             */
/*   Updated: 2024/11/26 14:42:58 by clouaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
    t_table table;

    if (ac != 5 && ac != 6)
        return (printf("Error: wrong number of arguments\n"));
    if (init_table(&table, ac, av))
        return (printf("Error: table initialization failed\n"));
    if (start_simulation(&table))
        return (printf("Error: simulation failed\n"));
    return (0);
}