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

		for (const val of data.data) {
			console.log(val);
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
			const key = `${val.name} (${val.semester}-${val.year})`;
			if (!(key in aggregated)) {
				aggregated[key] = [];
			}

			aggregated[key].push(val);
		}

		for (const k in aggregated) {
			const enrollment = aggregated[k];
			const enrollmentData = {
				ratingCount: 0,
				ratingTotal: 0,
				comments: []
			};

			for (const v of enrollment) {
				enrollmentData.ratingCount++;
				enrollmentData.ratingTotal += v.rating;
				enrollmentData.comments.push(v.comments);
			}

			const card = document.createElement('div');
			card.className = 'card';

			const header = document.createElement('div');
			header.className = 'card-header';
			header.innerText = k;

			const body = document.createElement('div');
			body.className = 'card-body';

			const text = document.createElement('div');
			text.className = 'card-text';

			text.innerText = `Total ratings: ${enrollmentData.ratingCount}\nAverage Rating: ${enrollmentData.ratingTotal / enrollmentData.ratingCount}\nComments: ${enrollmentData.comments}`;

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
	}
});
