/*
 * This file is part of the sigrok project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef SIGSESSION_H
#define SIGSESSION_H

#include <boost/shared_ptr.hpp>

#include <list>
#include <map>
#include <string>

#include <QObject>

extern "C" {
#include <libsigrok/libsigrok.h>
}

class LogicData;
class LogicDataSnapshot;
class Signal;

class SigSession : public QObject
{
	Q_OBJECT

public:
	SigSession();

	~SigSession();

	void loadFile(const std::string &name);

private:
	void dataFeedIn(const struct sr_dev_inst *sdi,
		struct sr_datafeed_packet *packet);

	static void dataFeedInProc(const struct sr_dev_inst *sdi,
		struct sr_datafeed_packet *packet);

private:
	std::list< boost::shared_ptr<Signal> > _signals;
	boost::shared_ptr<LogicData> _logic_data;
	boost::shared_ptr<LogicDataSnapshot> _cur_logic_snapshot;

signals:
	void dataUpdated();

private:
	// TODO: This should not be necessary. Multiple concurrent
	// sessions should should be supported and it should be
	// possible to associate a pointer with a sr_session.
	static SigSession *session;
};

#endif // SIGSESSION_H