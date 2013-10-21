/*  Copyright (C) 2013 Ben Asselstine

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/
#include <config.h>
#include <stdlib.h>
#include <unistd.h>
#include "licensing_priv.h"
#include "isc.h"
#include "gettext-more.h"
#include "xvasprintf.h"
#include "read-file.h"
#include "util.h"

static struct argp_option argp_options[] = 
{
    {"list-licenses", 'l', NULL, OPTION_HIDDEN, N_("show licenses and exit")},
    {0}
};

static error_t 
parse_opt (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
    case 'l':
        {
          char **license = isc.licenses;
          while (*license)
            fprintf (stdout, "%s\n", *license++);
          exit (0);
        }
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

#undef ISC_DOC
#define ISC_DOC N_("Show the ISC (OpenBSD) License.")
static struct argp argp = { argp_options, parse_opt, "", ISC_DOC};

int 
lu_isc_parse_argp (struct lu_state_t *state, int argc, char **argv)
{
  int err = 0;
  struct lu_isc_options_t opts;
  opts.state = state;

  err = argp_parse (&argp, argc, argv, state->argp_flags,  0, &opts);
  if (!err)
    return lu_isc (state, &opts);
  else
    return err;
}

int
show_lu_isc(struct lu_state_t *state, struct lu_isc_options_t *options)
{
  char *url = strdup ("http://directory.fsf.org/wiki/License:ISC");
  int err = 0;
  char tmp[sizeof(PACKAGE) + 13];
  snprintf (tmp, sizeof tmp, "/tmp/%s.XXXXXX", PACKAGE);
  int fd = mkstemp(tmp);
  close (fd);
  FILE *fileptr = fopen (tmp, "wb");
  curl_easy_setopt (state->curl, CURLOPT_HTTPGET, 1);
  curl_easy_setopt (state->curl, CURLOPT_URL, url);
  curl_easy_setopt (state->curl, CURLOPT_WRITEDATA, fileptr);
  curl_easy_perform(state->curl);
  fflush (fileptr);
  fsync (fileno (fileptr));
  fclose (fileptr);
  fileptr = fopen (tmp, "r");
  size_t data_len = 0;
  char *data = fread_file (fileptr, &data_len);
  fclose (fileptr);
  remove (tmp);

  replace_html_entities (data);
  show_lines_after (state, data, "Permission to use, copy, modify, ", 12, 0, 
                      NULL, NULL);
  free (url);
  free (data);
  return err;
}

int 
lu_isc (struct lu_state_t *state, struct lu_isc_options_t *options)
{
  int err = 0;
  err = show_lu_isc(state, options);
  return err;
}

struct lu_command_t isc = 
{
  .name         = N_("isc"),
  .doc          = ISC_DOC,
  .flags        = IS_A_LICENSE | DO_NOT_SHOW_IN_HELP | SAVE_IN_HISTORY,
  .argp         = &argp,
  .parser       = lu_isc_parse_argp,
  .licenses     = 
    { 
      "isc isc",
      "openbsd isc",
      NULL
    }
};
