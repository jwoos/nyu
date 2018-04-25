'use strict';


const storage = window.localStorage;

const BASE = '/api';

const ACCOUNT_KEY = 'account';
const TOKEN_KEY = 'token';


window.common = {
	setAccount: (user) => {
		storage.setItem(ACCOUNT_KEY, JSON.stringify(user));
	},

	getAccount: (user) => {
		return JSON.parse(storage.getItem(ACCOUNT_KEY));
	},

	clearAccount: () => {
		storage.removeItem(ACCOUNT_KEY);
	},

	setToken: (token) => {
		storage.setItem(TOKEN_KEY, token);
	},

	getToken: (token) => {
		return storage.getItem(TOKEN_KEY);
	},

	clearToken: (token) => {
		storage.removeItem(TOKEN_KEY);
	},

	checkAuthentication: (home) => {
		const token = window.common.getToken();
		const account = window.common.getAccount();

		if (home) {
			if (token && account) {
				switch (account.class) {
					case 'student':
						window.location.replace(`/${account.class}/evaluation.html`);
						break;

					case 'professor':
						window.location.replace(`/${account.class}/history.html`);
						break;
				}
			}
		} else {
			if (token && account) {

				return true;
			} else {
				window.common.notAuthenticated();

				return false;
			}
		}
	},

	notAuthenticated: () => {
		window.common.clearToken();
		window.common.clearAccount();
		window.location.replace('/');
	}
};
