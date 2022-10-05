/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_man.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:21:03 by briffard          #+#    #+#             */
/*   Updated: 2022/08/01 12:28:33 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_usage(void)
{
	write (1, "usage: lem-in [-vmh] < source_file\n", 35);
}

void	print_bold(char *text)
{
	ft_putstr("\033[1m");
	ft_putstr(text);
	ft_putstr("\033[0m");
}

void	print_man(void)
{
	print_bold("\nNAME\n");
	ft_putstr("\tLem-in\n");
	print_bold("\nSYNOPSIS\n\t");
	print_usage();
	print_bold("\nDESCRIPTION\n");
	ft_putstr("\tWe make an ant farm, with tunnels and rooms. We place the ants \
on one side, and we look at how they find the exit.\n");
	ft_putstr("\tWe join the rooms to one another with as many tubes as we \
need. A tube joins two rooms to each other.\n");
	ft_putstr("\tA room can be linked to an infinite number of rooms and by as \
many tubes as deemed necessary.\n\tThen we must bury the ant farm \
(wherever you want).\n\tThis is extremely important to ensure that \
ants don’t cheat and look at your design before before the game \
starts.\n");
	ft_putstr("\nThe following options are available:\n\n");
	print_bold("\t-m");
	ft_putstr("\tDoesn't print the map on the standard output.\n");
	print_bold("\t-v");
	ft_putstr("\tActivates the graphic mode.\n");
	print_bold("\t-p");
	ft_putstr("\tPrints the paths taken by the ants.\n");
	print_bold("\t-h");
	ft_putstr("\tDisplays man of the program.\n\n");
}
