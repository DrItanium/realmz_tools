maya is a fork/partial rewrite of clips 6.40 which takes all of the lessons I've learned using CLIPS in a
commercial environment. As time goes on I do plant to migrate all of the code to C++ but there are issues with
doing that in a piecemeal fashion (especially around how clips does memory management).

Here is what is different (not exhaustive):

- Source code has been renamed from the 8.3 style to an expanded form (much much easier to read)
- Merger of some concepts (there is only Fact.h now for example)
- Removal of BLOAD, BLOAD_ONLY, CONSTRUCT_PARSER, TEXTPRO_COMMANDS, and RUN_TIME completely
  - CONSTRUCT_COMPILER has its uses but for what I've used CLIPS for (code generation, parsing, and knowledge construction)
    having a single fixed expert system embedded into the program itself is useless.
    - Another downside to the construct compiler is that if you want to use c++ LAMBDA functions then you can't pass a name
      to the construct compiler. We do use lambdas as the function body of UDFs at work so we will never be able to use the
      construct compiler.
    - Even if we wanted to use the RUN_TIME feature, we would have to build two copies of the CLIPS code to leverage it and
      frankly that is a management nightmare. I do see the uses of this feature but I've never needed to leverage it.
    - BLOAD_AND_BSAVE is the only valid combination at this point. I can see BLOAD being useful but it requires separate
      build setups (once again increasing the potential for problems)
  - BLOAD_ONLY is useless because we use the same executable to generate the binary images as we do to load them.
    Plus bload only makes it much harder to debug problems we get reported to us from the field
  - TEXTPRO_COMMANDS do not seem to be used at all but even if it was I have never been able to figure out how it works fully (probably why it was removed by stock clips)
  - NOTE: This change _breaks_ compatibility with stock clips! I modified the signatures of AddUDF and various other functions
    as a side effect of removing the construct compiler
- DEFRULE_CONSTRUCT option has been removed and is always active
  - CLIPS is a wonderful scripting language but I have never seen the need to disable defrule. In fact, I feel that if all one
  needs is a scripting language but not defrules, templates, and facts then LUA is a much better target. Thus defrule is always
  available
- The object system is now always active. The object system is another very cool aspect of CLIPS that I always like having access to.
- Platform autodetection
  - In general, the OperatingSystemShim.h should do a relatively decent job of detecting what platform you are running
    on and automatically configure the appropriate macros in Setup.h.
- CMake Build System
  - I was using a makefile but since I've switch to CLion, I find that cmake is much easier to use and I do not have
    constantly keep track of dependencies manually. Plus, clion works wonderfully with cmake.
- Extended functions
  - Routines from boost are pulled in to provide even better string and filesystem support (has-prefix, filep, etc)
  - New functional and multifield (empty$) routines are also provided

My maya fork was originally known as the electron platform but I renamed it to maya because... well I can't remember 
exactly why at this point in time.

I will sync changes in from CLIPS itself but I never plan to merge these changes back because I do not think that CLIPS 
is broken. I am only leveraging its functionality.