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
#pragma once
#include <librevault/Meta.h>
#include <librevault/Secret.h>
#include <QList>
#include <QVariantMap>
#include <QString>
#include <QUrl>
#include <chrono>

namespace librevault {

struct FolderParams {
	enum class ArchiveType : unsigned {
		NO_ARCHIVE = 0,
		TRASH_ARCHIVE,
		TIMESTAMP_ARCHIVE,
		BLOCK_ARCHIVE
	};

	FolderParams(QVariantMap fconfig);

	/* Parameters */
	Secret secret;
	QString path;
	QString system_path;
	std::chrono::milliseconds index_event_timeout;
	bool preserve_unix_attrib;
	bool preserve_windows_attrib;
	bool preserve_symlinks;
	bool normalize_unicode;
	Meta::StrongHashType chunk_strong_hash_type;
	std::chrono::seconds full_rescan_interval;
	QStringList ignore_paths;
	QList<QUrl> nodes;
	ArchiveType archive_type;
	unsigned archive_trash_ttl;
	unsigned archive_timestamp_count;
	bool mainline_dht_enabled;
};

} /* namespace librevault */
