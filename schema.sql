CREATE TABLE IF NOT EXISTS drivers (
  driver_id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT,
  x REAL,
  y REAL,
  status TEXT,
  rating REAL DEFAULT 5.0,
  rating_count INTEGER DEFAULT 0
);

CREATE TABLE IF NOT EXISTS passengers (
  passenger_id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT,
  x REAL,
  y REAL
);

CREATE TABLE IF NOT EXISTS rides (
  ride_id INTEGER PRIMARY KEY AUTOINCREMENT,
  passenger_id INTEGER,
  driver_id INTEGER,
  start_x REAL,
  start_y REAL,
  end_x REAL,
  end_y REAL,
  fare REAL,
  status TEXT
);
