/*  Copyright (C) 2013 Ben Asselstine

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/
#ifndef LU_BSD_H
#define LU_BSD_H 1

#include <config.h>
#include <argp.h>
#include "licensing.h"

struct lu_bsd_options_t
{
  struct lu_state_t *state;
  int clause;
};

int lu_bsd_parse_argp (struct lu_state_t *, int argc, char **argv);
int lu_bsd (struct lu_state_t *, struct lu_bsd_options_t *);
extern struct lu_command_t bsd;
#endif
