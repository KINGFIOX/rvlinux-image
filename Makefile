up:
	docker compose up -d

attach:
	docker compose exec -it rvlinux bash

down:
	docker compose down

build:
	cd docker && docker build . -t rvlinux
