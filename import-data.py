#!/usr/bin/env python3
# usage: import-data <airports CSV> <routes CSV>

OUTPUT_FILE_AIRPORTS = 'data/airports-preprocessed.csv'
OUTPUT_FILE_ROUTES = 'data/routes-preprocessed.csv'
NULL = '\\N'

import csv
import sys

# import airports
airports = {}
with open(OUTPUT_FILE_AIRPORTS, 'w', encoding = 'utf-8') as f_out_airports:
	writer = csv.writer(f_out_airports)
	writer.writerow(['ID', 'lat', 'long', 'IATA', 'ICAO', 'name'])
	with open(sys.argv[1], encoding = 'utf-8') as f_airports_csv:
		reader = csv.reader(f_airports_csv)
		for row in reader:
			ID = row[0]
			name = row[1]
			IATA = row[4]
			ICAO = row[5]
			latitude = row[6]
			longitude = row[7]
			if IATA == NULL:
				IATA = ''
			if ICAO == NULL:
				ICAO = ''
			if ICAO == '':
				# skip airports with no ICAO code defined
				continue
			writer.writerow([ID, latitude, longitude, IATA, ICAO, name])
			airports[ID] = {
				'name': name,
				'IATA': IATA,
				'ICAO': ICAO,
				'latitude': latitude,
				'longitude': longitude
			}

# import routes
with open(OUTPUT_FILE_ROUTES, 'w', encoding = 'utf-8') as f_out_routes:
	writer = csv.writer(f_out_routes)
	writer.writerow([
		'src airport ID', 'src airport lat', 'src airport long',
		'dst airport ID', 'dst airport lat', 'dst airport long'])
	with open(sys.argv[2], encoding = 'utf-8') as f_routes_csv:
		reader = csv.reader(f_routes_csv)
		for row in reader:
			stops = int(row[7])
			if stops != 0:
				# skip non-direct routes
				continue
			src_airport_ID = row[3]
			dst_airport_ID = row[5]
			if src_airport_ID == NULL or dst_airport_ID == NULL:
				# skip if we don't know the source or the destination
				continue
			try:
				src_airport = airports[src_airport_ID]
				dst_airport = airports[dst_airport_ID]
			except KeyError:
				# skip routes involving undefined airports
				continue
			src_airport_lat  = src_airport['latitude']
			src_airport_long = src_airport['longitude']
			dst_airport_lat  = dst_airport['latitude']
			dst_airport_long = dst_airport['longitude']
			writer.writerow([
				src_airport_ID, src_airport_lat, src_airport_long,
				dst_airport_ID, dst_airport_lat, dst_airport_long])
