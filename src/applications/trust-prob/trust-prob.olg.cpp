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
materialize(trust, infinity, infinity, keys(1, 2:int32, 3:int32, 4:int32)).
materialize(trustPath, infinity, infinity, keys(1, 2:int32, 3:int32, 4:int32)).
materialize(trustEvent, infinity, infinity, keys(1, 2:int32, 3:int32, 4:int32)).
materialize(mutualTrustPath, infinity, infinity, keys(1, 2:int32, 3:int32, 4:int32)).
materialize(provEdge, infinity, infinity, keys(1, 2, 3)).
materialize(ruleEdge, infinity, infinity, keys(1, 2, 3)).
// ra 1.0 trustEvent(@Local, P1, P2) :- trustPath(@Local, P1, P2).
ra_1 1.0 etrustEvent(@Local, P1, P2, RID, HVID, BVID, RC, HC, BC, R) :- trustPath(@Local, P1, P2, R),
                  RC := "ra_trustPath_"+P1+"_"+P2, HC := "trustEvent"+P1+"-"+P2, BC := "trustPath"+P1+"-"+P2,
                                   RID := f_sha1("ra"+"trustPath"+P1+P2), HVID := f_sha1("trustEvent"+P1+P2), BVID := f_sha1("trustPath"+P1+P2).
ra_2 trustEvent(@Local, P1, P2, R) :- etrustEvent(@Local, P1, P2, RID, HVID, BVID, RC, HC, BC, R).
ra_3 insertProvEdge(@Local, HVID, RID, HC, RC) :- etrustEvent(@Local, P1, P2, RID, HVID, BVID, RC, HC, BC, R).
ra_4 insertRuleEdge(@Local, RID, BVID, RC, BC) :- etrustEvent(@Local, P1, P2, RID, HVID, BVID, RC, HC, BC, R).
// r1 1.0 trustPath(@Local, P1, P2) :- trust(@Local, P1, P2).
r1_1 1.0 etrustPath(@Local, P1, P2, RID, HVID, BVID, RC, HC, BC, R) :- trust(@Local, P1, P2, R),
          RC := "r1_trust_"+P1+"_"+P2, HC := "trustPath"+P1+"-"+P2, BC := "trust"+P1+"-"+P2,
          RID := f_sha1("r1"+"trust"+P1+P2), HVID := f_sha1("trustPath"+P1+P2), BVID := f_sha1("trust"+P1+P2).
r1_2 trustPath(@Local, P1, P2, R) :- etrustPath(@Local, P1, P2, RID, HVID, BVID, RC, HC, BC, R).
r1_3 insertProvEdge(@Local, HVID, RID, HC, RC) :- etrustPath(@Local, P1, P2, RID, HVID, BVID, RC, HC, BC, R).
r1_4 insertRuleEdge(@Local, RID, BVID, RC, BC) :- etrustPath(@Local, P1, P2, RID, HVID, BVID, RC, HC, BC, R).
// r2 0.8 trustPath(@Local, P1, P3) :- trust(@Local, P1, P2), trustPath(@Local, P2, P3), P1!=P3.
r2_1 0.8 etrustPathR2(@Local, P1, P3, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R) :- trust(@Local, P1, P2, R), trustPath(@Local, P2, P3, R), P1!=P3,
          RC := "r2_trust_"+P1+"_"+P2+"_trustPath_"+P2+"_"+P3, HC := "trustPath"+P1+"-"+P3, BC1 := "trust"+P1+"-"+P2, BC2 := "trustPath"+P2+"-"+P3,
          RID := f_sha1("r2"+"trust"+P1+P2+"trustPath"+P2+P3), HVID := f_sha1("trustPath"+P1+P3), BVID1 := f_sha1("trust"+P1+P2), BVID2 := f_sha1("trustPath"+P2+P3).
r2_2 trustPath(@Local, P1, P3, R) :- etrustPathR2(@Local, P1, P3, RID, HVID, BVID1, BVID2, HC, RC, BC1, BC2, R).
r2_3 insertProvEdge(@Local, HVID, RID, HC, RC) :- etrustPathR2(@Local, P1, P3, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R).
r2_4 insertRuleEdge(@Local, RID, BVID1, RC, BC1) :- etrustPathR2(@Local, P1, P3, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R).
r2_5 insertRuleEdge(@Local, RID, BVID2, RC, BC2) :- etrustPathR2(@Local, P1, P3, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R).
// r3 0.8 mutualTrustPath(@Local, P1, P2) :- trustEvent(@Local, P1, P2), trustPath(@Local, P2, P1).
r3_1 1.0 emutualTrustPath(@Local, P1, P2, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R) :- trustEvent(@Local, P1, P2, R), trustPath(@Local, P2, P1, R),
        RC := "r3_trustEvent_"+P1+"_"+P2+"_trustPath_"+P2+"_"+P1, HC := "mutualTrustPath"+P1+"-"+P2, BC1 := "trustEvent"+P1+"-"+P2, BC2 := "trustPath"+P2+"-"+P1,
        RID := f_sha1("r3"+"trustEvent"+P1+P2+"trustPath"+P2+P1), HVID := f_sha1("mutualTrustPath"+P1+P2), BVID1 := f_sha1("trustEvent"+P1+P2), BVID2 := f_sha1("trustPath"+P2+P1).
r3_2 mutualTrustPath(@Local, P1, P2, R) :- emutualTrustPath(@Local, P1, P2, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R).
r3_3 insertProvEdge(@Local, HVID, RID, HC, RC) :- emutualTrustPath(@Local, P1, P2, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R).
r3_4 insertRuleEdge(@Local, RID, BVID1, RC, BC1) :- emutualTrustPath(@Local, P1, P2, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R).
r3_5 insertRuleEdge(@Local, RID, BVID2, RC, BC2) :- emutualTrustPath(@Local, P1, P2, RID, HVID, BVID1, BVID2, RC, HC, BC1, BC2, R).
re_1 provEdgeCount(@Local, HVID, RID, HC, RC, a_count<*>) :- insertProvEdge(@Local, HVID, RID, HC, RC), provEdge(@Local, HVID, RID, HC, RC, N).
re_2 provEdge(@Local, HVID, RID, HC, RC, N) :- provEdgeCount(@Local, HVID, RID, HC, RC, C), C==0, N:=1.
re_3 provEdge(@Local, HVID, RID, HC, RC, N1) :- provEdgeCount(@Local, HVID, RID, HC, RC, C), provEdge(@Local, HVID, RID, HC, RC, N), C>0, N1:=N+1.
re_4 ruleEdgeCount(@Local, RID, BVID, RC, BC, a_count<*>) :- insertRuleEdge(@Local, RID, BVID, RC, BC), ruleEdge(@Local, RID, BVID, RC, BC, N).
re_5 ruleEdge(@Local, RID, BVID, RC, BC, N) :- ruleEdgeCount(@Local, RID, BVID, RC, BC, C), C==0, N:=1.
re_6 ruleEdge(@Local, RID, BVID, RC, BC, N1) :- ruleEdgeCount(@Local, RID, BVID, RC, BC, C), ruleEdge(@Local, RID, BVID, RC, BC, N), C>0, N1:=N+1.
