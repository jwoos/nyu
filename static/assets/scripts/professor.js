'use strict';

window.common.checkAuthentication(false);

window.professor = {
	token: window.common.getToken(),
	account: window.common.getAccount(),

	populateCourses: async () => {
		const response = await fetch(`${BASE}/professors/${window.professor.account.id}/courses`, {
			method: 'GET',
			headers: {'Authorization': window.professor.token}
		});

		if (response.status === 401) {
			window.common.notAuthenticated();
			return;
		}

		const data = await response.json();

		const courseTag = document.querySelector('#courses');

		for (const val of data.data) {
			const card = document.createElement('div');
			card.className = 'card';

			const header = document.createElement('div');
			header.className = 'card-header';
			header.innerText = val.name;

			const body = document.createElement('div');
			body.className = 'card-body';

			const text = document.createElement('div');
			text.className = 'card-text';

			text.innerText = val.description;

			body.appendChild(text);
			card.appendChild(header);
			card.appendChild(body);

			courseTag.appendChild(card);
		}
	},

	populateEvaluations: async () => {
		const response = await fetch(`${BASE}/professors/${window.professor.account.id}/evaluations`, {
			method: 'GET',
			headers: {'Authorization': window.professor.token}
		});

		if (response.status === 401) {
			window.common.notAuthenticated();
			return;
		}

		const data = await response.json();

		const evalTag = document.querySelector('#evaluations');

		const aggregated = {};

		for (const val of data.data) {
			const key = `${val.name}`;
			if (!(key in aggregated)) {
				aggregated[key] = {};
			}

			const subkey = `${val.semester}-${val.year}`;
			if (!(subkey in aggregated[key])) {
				aggregated[key][subkey] = [];
			}

			aggregated[key][subkey].push(val);
		}

		for (const key in aggregated) {
			const semesterYear = aggregated[key];
			const semesterYearData = {};

			for (const subkey in semesterYear) {
				if (!(subkey in semesterYearData)) {
					semesterYearData[subkey] = {
						ratingCount: 0,
						ratingTotal: 0,
						comments: []
					};
				}

				for (const d of semesterYear[subkey]) {
					semesterYearData[subkey].ratingCount++;
					semesterYearData[subkey].ratingTotal += d.rating;
					semesterYearData[subkey].comments.push(d.comments);
				}
			}

			console.log(semesterYearData);

			const canvas = document.createElement('canvas');
			const chart = new Chart(canvas.getContext('2d'), {
				type: 'line',
				data: {
					labels: Object.keys(semesterYearData),
					datasets: [
						{
							label: 'Average Rating',
							data: Object.values(semesterYearData).map(x => x.ratingTotal / x.ratingCount),
							fill: false,
							borderColor: randomColor({luminosity: 'light', hue: 'random', format: 'rgb'}),
							lineTension: 0.1
						},
						{
							label: 'Total Rating',
							data: Object.values(semesterYearData).map(x => x.ratingCount),
							fill: false,
							borderColor: randomColor({luminosity: 'dark', hue: 'random', format: 'rgb'}),
							lineTension: 0.1
						}
					]
				},
				options:{}
			});

			const card = document.createElement('div');
			card.className = 'card';

			const header = document.createElement('div');
			header.className = 'card-header';
			header.innerText = key;

			const body = document.createElement('div');
			body.className = 'card-body';

			const text = document.createElement('div');
			text.className = 'card-text';

			text.innerText = `Comments:\n${Object.values(semesterYearData).map(x => x.comments.join('\n')).join('\n')}`;

			body.appendChild(canvas);
			body.appendChild(text);
			card.appendChild(header);
			card.appendChild(body);

			evalTag.appendChild(card);
		}
	}
};

window.addEventListener('load', async () => {
	switch (window.location.pathname) {
		case '/professor/history.html':
			await window.professor.populateEvaluations();
			break;

		case '/professor/course.html':
			await window.professor.populateCourses();
			break;
	}
	document.querySelector("#logOut").addEventListener('click',function(){
		window.common.clearToken();
		window.common.clearAccount();
		window.location.replace('/');
	});
});
