/* vim: set et ts=4 sw=4 ft=cpp:
 *
 * Copyright (C) 2011 James McLaughlin.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "../Common.h"

struct Lacewing::Event::Internal
{
};

Event::Event()
{
    LacewingInitialise();

    internal = (Lacewing::Event::Internal *) WSACreateEvent ();
    Tag = 0;
}

Event::~Event()
{
    WSACloseEvent ((WSAEVENT) internal);
}

bool Event::Signalled()
{
    return WSAWaitForMultipleEvents
        (1, (WSAEVENT *) &internal, true, 0, false) == WAIT_OBJECT_0;
}

void Event::Signal()
{
    WSASetEvent ((WSAEVENT) internal);
}

void Event::Unsignal()
{
    WSAResetEvent ((WSAEVENT) internal);
}

bool Event::Wait(int Timeout)
{
    return WSAWaitForMultipleEvents
        (1, (WSAEVENT *) &internal, true, Timeout == -1 ? INFINITE : Timeout, false)
            == WAIT_OBJECT_0;
}
