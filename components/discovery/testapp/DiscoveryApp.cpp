/* Copyright (C) 2016 Alexander Shishenko <alex@shishenko.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
#include "DiscoveryApp.h"
#include "Discovery.h"
#include "DiscoveryGroup.h"
#include <QDebug>
#include <QtGlobal>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <chrono>

namespace librevault {

DiscoveryApp::DiscoveryApp(int argc, char** argv, const char* USAGE) : QCoreApplication(argc, argv) {
	args = docopt::docopt(USAGE, {argv + 1, argv + argc}, true);

	QByteArray id = QByteArray::fromHex(QByteArray::fromStdString(args["<id>"].asString()));
	discovery = new Discovery(this);
	dgroup = discovery->createGroup(id);

	connect(dgroup, &DiscoveryGroup::discovered, this, &DiscoveryApp::handleDiscovered);

	discovery->setAnnounceLANPort(12345);
	discovery->startMulticast(QHostAddress("239.192.152.144"), 28914, QHostAddress("ff08::BD02"), 28914);
	dgroup->setMulticastEnabled(true);
	dgroup->setMulticastInterval(std::chrono::seconds(5));
}

void DiscoveryApp::handleDiscovered(QHostAddress addr, quint16 port) {
	qDebug() << "Discovered: " << addr.toString() << " " << port;
}

} /* namespace librevault */