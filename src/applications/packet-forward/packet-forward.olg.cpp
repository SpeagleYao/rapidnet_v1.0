/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
materialize(packet, infinity, infinity, keys(1, 2, 3, 4)).
materialize(route, infinity, infinity, keys(1, 2, 3)).
materialize(recv, infinity, infinity, keys(1, 2, 3, 4)).
materialize(edge, infinity, infinity, keys(1, 2, 3)).
materialize(prov, infinity, infinity, keys(1, 2, 3)).
// r1 packet(@N, S, D, DT) :- packet(@L, S, D, DT), route(@L, D, N).
r1_1 epacket(@N, S, D, DT, L, RID, HVID, BVID) :- packet(@L, S, D, DT), route(@L, D, N),
            PID1 := f_sha1("route"+L+D+N), PID := f_append(PID1),
            RID := f_sha1("r1"+N+PID),
            HVID := "packet"+N+S+D,
            BVID := "packet"+L+S+D.
r1_2 packet(@N, S, D, DT) :- epacket(@N, S, D, DT, L, RID, HVID, BVID).
r1_3 prov(@N, HVID, RID) :- epacket(@N, S, D, DT, L, RID, HVID, BVID).
r1_4 insertedge(@N, RID1, RID2) :- epacket(@N, S, D, DT, L, RID1, HVID, BVID), prov(@L, BVID, RID2).
// r2 recv(@L, S, D, DT) :- packet(@L, S, D, DT), D==L.
r2_1 erecv(@L, S, D, DT, RID, HVID, BVID) :- packet(@L, S, D, DT), D==L,
              RID := f_sha1("r2"+L),
              HVID := "recv"+L+S+D,
          BVID := "packet"+L+S+D.
r2_2 recv(@L, S, D, DT) :- erecv(@L, S, D, DT, RID, HVID, BVID).
r2_3 prov(@L, HVID, RID) :- erecv(@L, S, D, DT, RID, HVID, BVID).
r2_4 insertedge(@L, RID1, RID2) :- erecv(@L, S, D, DT, RID1, HVID, BVID), prov(@L, BVID, RID2).
re_1 edgeCount(@Local, RID1, RID2, a_COUNT<*>) :- insertedge(@Local, RID1, RID2), edge(@Local, RID1, RID2, N).
re_2 edge(@Local, RID1, RID2, N) :- edgeCount(@Local, RID1, RID2, C), C == 0, N := 1.
re_3 edge(@Local, RID1, RID2, N1) :- edgeCount(@Local, RID1, RID2, C), edge(@Local, RID1, RID2, N), C > 0, N1 := N+1.
