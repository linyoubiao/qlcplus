/*
  Q Light Controller
  genericfader.h

  Copyright (c) Heikki Junnila

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef GENERICFADER
#define GENERICFADER

#include <QList>
#include <QHash>

#include "universe.h"

class FadeChannel;

/** @addtogroup engine Engine
 * @{
 */

class GenericFader
{
public:
    GenericFader();
    ~GenericFader();

    int priority() const;
    void setPriority(int priority);

    static quint32 channelHash(quint32 fixtureID, quint32 channel);

    /**
     * Add a channel that shall be faded from ch.start() to ch.target() within
     * the time specified by ch.fadeTime(). If ch.target() == 0, the channel will
     * be removed automatically from the fader when done.
     *
     * If the fader already contains the same channel, the one whose current
     * value is higher remains in the fader. With LTP channels this might result
     * in the value jumping in a weird way but LTP channels are rarely faded anyway.
     * With HTP channels the lower value has no meaning in the first place.
     *
     * @param ch The channel to fade
     */
    void add(const FadeChannel& ch);

    /** Replace an existing FaderChannel */
    void replace(const FadeChannel& ch);

    /** Remove a channel whose fixture & channel match with $fc's */
    void remove(FadeChannel *ch);

    /** Remove all channels */
    void removeAll();

    /** Get/Set a request of deletion of this fader */
    bool deleteRequest();
    void requestDelete();

    /** Returns a reference of a FadeChannel for the provided $fixtureID and $channel.
     *  If no FadeChannel is found, a new one is created and added to m_channels.
     *  Also, new channels will have a start value set depending on their type */
    FadeChannel *getChannelFader(const Doc *doc, Universe *universe, quint32 fixtureID, quint32 channel);

    /** Get all channels in a non-modifiable hashmap */
    const QHash <quint32,FadeChannel>& channels() const;

    /** Return the number of channel added to this fader */
    int channelsCount() const;

    /**
     * Run the channels forward by one step and write their current values to
     * the given Universe
     *
     * @param universe The universe that receives channel data.
     */
    void write(Universe *universe);

    /** Get/Set the intensities of all channels in a 0.0 - 1.0 range */
    qreal intensity() const;
    void adjustIntensity(qreal fraction);

    /** Get/Set the pause state of this fader */
    bool isPaused() const;
    void setPaused(bool paused);

    /** Get/Set the enable state of this fader */
    bool isEnabled() const;
    void setEnabled(bool enable);

    /** Get the fade out status of this fader */
    bool isFadingOut() const;

    /** Set this fader to fade out. If $fadeTime is non-zero,
      * all the intensity channels will be updated */
    void setFadeOut(bool enable, uint fadeTime);

    /**
     * Set the blend mode to be applied in the write method
     *
     * @param mode the blend mode as listed in Universe::BlendMode
     */
    void setBlendMode(Universe::BlendMode mode);

private:
    int m_priority;
    QHash <quint32,FadeChannel> m_channels;
    qreal m_intensity;
    bool m_paused;
    bool m_enabled;
    bool m_fadeOut;
    bool m_deleteRequest;
    Universe::BlendMode m_blendMode;
};

/** @} */

#endif
